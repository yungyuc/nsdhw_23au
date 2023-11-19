#include <limits>
#include <iostream>
#include <mkl.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

struct ByteCounterImpl {

    size_t allocated = 0;
    size_t deallocated = 0;
    size_t refcount = 0;

}; 

class ByteCounter {

public:

    ByteCounter()
      : m_impl(new ByteCounterImpl) {
        incref(); 
        }

    ByteCounter(ByteCounter const & other)
      : m_impl(other.m_impl) {
        incref(); 
        }

    ByteCounter & operator=(ByteCounter const & other) {
        if (&other != this) {
            decref();
            m_impl = other.m_impl;
            incref();
        }

        return *this;
    }

    ByteCounter(ByteCounter && other)
      : m_impl(other.m_impl) {
        incref(); 
        }

    ByteCounter & operator=(ByteCounter && other) {
        if (&other != this) {
            decref();
            m_impl = other.m_impl;
            incref();
        }

        return *this;
    }

    ~ByteCounter() {
        decref(); 
    }

    void swap(ByteCounter & other) {
        swap(m_impl, other.m_impl);
    }

    void increase(size_t amount) {
        m_impl->allocated += amount;
    }

    void decrease(size_t amount) {
        m_impl->deallocated += amount;
    }

    size_t bytes() const { 
        return m_impl->allocated - m_impl->deallocated; 
        }

    size_t allocated() const { 
        return m_impl->allocated; 
        }
    size_t deallocated() const { 
        return m_impl->deallocated; 
        }
    size_t refcount() const { 
        return m_impl->refcount; 
        }

private:

    void incref() { 
        ++m_impl->refcount; 
    }

    void decref() {
        if (nullptr == m_impl) {}
        else if (1 == m_impl->refcount) {
            delete m_impl;
            m_impl = nullptr;
        }
        else {
            --m_impl->refcount;
        }
    }

    ByteCounterImpl * m_impl;

};

ByteCounter counter;

template <class T>
struct MyAllocator {

    using value_type = T;

    MyAllocator() = default;

    T * allocate(size_t n) {
        if (n > numeric_limits<size_t>::max() / sizeof(T)) {
            throw bad_alloc();
        }
        const size_t bytes = n*sizeof(T);
        T * p = static_cast<T *>(malloc(bytes));
        if (p) {
            counter.increase(bytes);
            return p;
        }
        else {
            throw bad_alloc();
        }
    }

    void deallocate(T* p, size_t n) noexcept {
        free(p);

        const size_t bytes = n*sizeof(T);
        counter.decrease(bytes);
    }
};

class Matrix {
public:
    Matrix(size_t nrow, size_t ncol) : m_nrow{ nrow }, m_ncol{ ncol } {
        m_buffer = vector<double, MyAllocator<double>>(nrow * ncol);
    }
    size_t const &nrow() const { 
        return m_nrow; 
    }

    size_t const &ncol() const { 
        return m_ncol; 
    }
    vector<double, MyAllocator<double>> const &buffer() const { 
        return m_buffer; 
    }
    vector<double, MyAllocator<double>> &buffer() { 
        return m_buffer;
    }
    double operator() (size_t row, size_t col) const { 
        return m_buffer[row * m_ncol + col]; 
    }
    double &operator() (size_t row, size_t col) { 
        return m_buffer[row * m_ncol + col]; 
    }
    bool operator== (const Matrix &m2) const {
        if (m_nrow != m2.nrow() || m_ncol != m2.ncol())
            return false;
        for (size_t i = 0; i < m_nrow * m_ncol; i++) {
            if (m_buffer[i] != m2.buffer()[i])
                return false;
        }
        return true;
    };
    bool operator!= (const Matrix &m2) const { 
        return !(m2 == (*this)); 
    }

private:
    size_t m_nrow;
    size_t m_ncol;
    vector<double, MyAllocator<double>> m_buffer;
    MyAllocator<size_t> alloc;
};



size_t bytes() { return counter.bytes(); }
size_t allocated() { return counter.allocated(); }
size_t deallocated() { return counter.deallocated(); }



Matrix multiply_naive(Matrix &mat1, Matrix &mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }
    Matrix ret(mat1.nrow(), mat2.ncol());
    for (size_t i=0; i<mat1.nrow(); ++i) {
        for (size_t k=0; k<mat2.ncol(); ++k) {
            double v = 0;
            for (size_t j=0; j<mat1.ncol(); ++j) {
                v += mat1(i,j) * mat2(j,k);
            }
            ret(i,k) = v;
        }
    }
    return ret;
}




Matrix multiply_mkl(const Matrix &mat1, const Matrix &mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }
    Matrix ret(mat1.nrow(), mat2.ncol());
    cblas_dgemm(
        CblasRowMajor,
        CblasNoTrans,
        CblasNoTrans,
        mat1.nrow(),
        mat2.ncol(),
        mat1.ncol(),
        1.0,
        mat1.buffer().data(),
        mat1.ncol(),
        mat2.buffer().data(),
        mat2.ncol(),
        0.0,
        ret.buffer().data(),
        ret.ncol()
    );
    return ret;
};




Matrix multiply_tile(Matrix const &mat1, Matrix const &mat2, size_t T) {
    validate_multiplication(mat1, mat2);
    size_t M = mat1.nrow();
    size_t N = mat2.ncol();
    size_t K = mat1.ncol();
    Matrix ret(mat1.nrow(), mat2.ncol());
    for (size_t m = 0; m < M; m += T) {
        for (size_t n = 0; n < N; n += T) {
            for (size_t k = 0; k < K; k += T) {
                const size_t minMt = std::min(m + T, M);
                const size_t minNt = std::min(n + T, N);
                const size_t minKt = std::min(k + T, K);
                for (size_t mt = m; mt < minMt; mt++) {
                    for (size_t nt = n; nt < minNt; nt++) {
                        for (size_t kt = k; kt < minKt; kt++) {
                            ret(mt, nt) += mat1(mt, kt) * mat2(kt, nt);
                        }
                    }
                }
            }
        }
    }
    return ret;
}




PYBIND11_MODULE(_matrix, m)
{
    m.doc() = "pybind11 example plugin"; 
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("__getitem__", [](const Matrix & mat, std::pair<size_t, size_t> pos) {
            return mat(pos.first, pos.second);
        })
        .def("__setitem__", [](Matrix & mat, std::pair<size_t, size_t> pos, float value) {
            mat(pos.first, pos.second) = value;
        })
        .def("__eq__", [](const Matrix & m1, const Matrix & m2) {
            return m1 == m2;
        })
        .def("__ne__", [](const Matrix & m1, const Matrix & m2) {
            return m1 != m2;
        });
    m.def("multiply_naive", &multiply_naive)
        .def("multiply_mkl", &multiply_mkl)
        .def("multiply_tile", &multiply_tile)
        .def("bytes", &bytes)
        .def("allocated", &allocated)
        .def("deallocated", &deallocated);
}