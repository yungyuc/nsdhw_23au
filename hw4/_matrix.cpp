#include <mkl.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>

#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>

struct MemoryTracker {
    std::size_t allocatedMemory = 0;
    std::size_t deallocatedMemory = 0;
    std::size_t refCount = 0;
};

class MemoryCounter {
public:
    MemoryCounter()
        : m_tracker(new MemoryTracker) {}

    void increase(std::size_t amount) {
        m_tracker->allocatedMemory += amount;
    }

    void decrease(std::size_t amount) {
        m_tracker->deallocatedMemory += amount;
    }

    std::size_t usedMemory() const { return m_tracker->allocatedMemory - m_tracker->deallocatedMemory; }
    std::size_t allocatedMemory() const { return m_tracker->allocatedMemory; }
    std::size_t deallocatedMemory() const { return m_tracker->deallocatedMemory; }

private:
    MemoryTracker* m_tracker;
};

template <class T>
struct CustomAllocator {

    using value_type = T;

    // Use the default constructor of MemoryCounter for the data member "memoryCounter".
    CustomAllocator() = default;

    T* allocate(std::size_t n) {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
            throw std::bad_alloc();
        }
        const std::size_t bytes = n * sizeof(T);
        T* p = static_cast<T*>(std::malloc(bytes));
        if (p) {
            memoryCounter.increase(bytes);
            return p;
        } else {
            throw std::bad_alloc();
        }
    }

    void deallocate(T* p, std::size_t n) noexcept {
        std::free(p);

        const std::size_t bytes = n * sizeof(T);
        memoryCounter.decrease(bytes);
    }

    MemoryCounter memoryCounter;

};

CustomAllocator<double> allocator;

std::size_t usedMemory() { return allocator.memoryCounter.usedMemory(); }
std::size_t allocatedMemory() { return allocator.memoryCounter.allocatedMemory(); }
std::size_t deallocatedMemory() { return allocator.memoryCounter.deallocatedMemory(); }

class Matrix {
public:
    size_t numRows;
    size_t numCols;

    Matrix(size_t numRows, size_t numCols)
        : numRows(numRows), numCols(numCols) {
        size_t numElements = numRows * numCols;
        dataBuffer.resize(numElements);
    }

    // No bound check.
    double operator()(size_t row, size_t col) const {
        return dataBuffer[row * numCols + col];
    }

    double& operator()(size_t row, size_t col) {
        return dataBuffer[row * numCols + col];
    }

    void loadFromPython(pybind11::array_t<double> input) {
        pybind11::buffer_info buf = input.request();
        memcpy(getData(), buf.ptr, numRows * numCols * sizeof(double));
    }

    void loadBuffer(double* input) {
        memcpy(getData(), input, numRows * numCols * sizeof(double));
    }

    friend bool operator==(const Matrix& A, const Matrix& B) {
        if ((A.numRows != B.numRows) || (A.numCols != B.numCols)) return false;
        for (size_t i = 0; i < A.numRows * A.numCols; i++) {
            if (A.dataBuffer[i] != B.dataBuffer[i]) return false;
        }
        return true;
    }

    double* getData() const {
        return (double*)&dataBuffer[0];
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "[";
        for (size_t row = 0; row < numRows; row++) {
            if (row > 0) {
                ss << " ";
            }

            ss << "[";
            for (size_t col = 0; col < numCols; col++) {
                ss << (*this)(row, col) << " ";
            }
            ss << "]";
            if (row < numRows - 1) {
                ss << std::endl;
            }
        }
        ss << "]";
        ss << std::endl;
        return ss.str();
    }

private:
    std::vector<double, CustomAllocator<double>> dataBuffer = std::vector<double, CustomAllocator<double>>(allocator);
};

Matrix multiplyNaive(Matrix& matrixA, Matrix& matrixB) {
    if (matrixA.numCols != matrixB.numRows) {
        throw pybind11::value_error("The shape of the two given matrices are not matched.");
    }

    Matrix result(matrixA.numRows, matrixB.numCols);
    for (size_t row = 0; row < matrixA.numRows; row++) {
        for (size_t col = 0; col < matrixB.numCols; col++) {
            for (size_t i = 0; i < matrixA.numCols; i++) {
                result(row, col) += matrixA(row, i) * matrixB(i, col);
            }
        }
    }
    return result;
}

Matrix multiplyTile(Matrix& matrixA, Matrix& matrixB, size_t tileSize) {
    if (matrixA.numCols != matrixB.numRows) {
        throw pybind11::value_error("The shape of the two given matrices are not matched.");
    }

    Matrix result(matrixA.numRows, matrixB.numCols);
    for (size_t tileRowStart = 0; tileRowStart < matrixA.numRows; tileRowStart += tileSize) {
        size_t tileRowEnd = tileRowStart + tileSize;
        tileRowEnd = (tileRowEnd > matrixA.numRows) ? matrixA.numRows : tileRowEnd;

        for (size_t tileColStart = 0; tileColStart < matrixB.numCols; tileColStart += tileSize) {
            size_t tileColEnd = tileColStart + tileSize;
            tileColEnd = (tileColEnd > matrixB.numCols) ? matrixB.numCols : tileColEnd;

            for (size_t t = 0; t < matrixA.numCols; t++) {
                for (size_t i = tileRowStart; i < tileRowEnd; i++) {
                    for (size_t j = tileColStart; j < tileColEnd; j++) {
                        result(i, j) += matrixA(i, t) * matrixB(t, j);
                    }
                }
            }
        }
    }
    return result;
}

Matrix multiplyMKL(Matrix& matrixA, Matrix& matrixB) {
    if (matrixA.numCols != matrixB.numRows) {
        throw pybind11::value_error("The shape of the two given matrices are not matched.");
    }

    double* C = new double[matrixA.numRows * matrixB.numCols];

    int m = matrixA.numRows;
    int k = matrixA.numCols;
    int n = matrixB.numCols;
    double alpha = 1.0, beta = 0.0;

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, alpha, matrixA.getData(), k, matrixB.getData(), n, beta, C, n);

    Matrix result(matrixA.numRows, matrixB.numCols);
    result.loadBuffer(C);

    delete[] C;

    return result;
}

PYBIND11_MODULE(_matrix, m) {
    m.doc() = "_matrix";

    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def("__getitem__", [](Matrix& mat, std::pair<size_t, size_t> index) {
            return mat(index.first, index.second);
        })
        .def("__setitem__", [](Matrix& mat, std::pair<size_t, size_t> index, double value) {
            mat(index.first, index.second) = value;
        })
        .def("__str__", [](Matrix& mat) {
            return mat.toString();
        })
        .def("load", &Matrix::loadFromPython)
        .def(pybind11::self == pybind11::self)
        .def_readonly("nrow", &Matrix::numRows)
        .def_readonly("ncol", &Matrix::numCols);

    m.def("multiply_naive", &multiplyNaive);
    m.def("multiply_tile", &multiplyTile);
    m.def("multiply_mkl", &multiplyMKL);
    m.def("bytes", &usedMemory);
    m.def("allocated", &allocatedMemory);
    m.def("deallocated", &deallocatedMemory);
}
