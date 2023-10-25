
#include <iostream>
#include <fstream>

#include <pybind11/pybind11.h> 
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <cblas.h>
//modify C/C++包含路徑
// #include <mkl.h>

class Matrix {

public:

    // 單一構造函數處理不同情況
    Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec = {})
        : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
        if (!vec.empty()) {
            (*this) = vec;
        }
    }

    // 處理構造函數和賦值運算符
    Matrix(const Matrix& other)
        : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(m_nrow, m_ncol);
        for (size_t i = 0; i < m_nrow; ++i) {
            for (size_t j = 0; j < m_ncol; ++j) {
                (*this)(i, j) = other(i, j);
            }
        }
    }

    Matrix(const std::initializer_list<std::initializer_list<double>>& data) {
        if (data.size() > 0) {
            m_nrow = data.size();
            m_ncol = data.begin()->size();
            reset_buffer(m_nrow, m_ncol);

            size_t i = 0, j = 0;
            for (const auto& row : data) {
                j = 0;
                for (const double& val : row) {
                    (*this)(i, j) = val;
                    ++j;
                }
                ++i;
            }
        }

    }

    Matrix& operator=(const Matrix& other)
    {
        if (this == &other) { return *this; }
        if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) {
            reset_buffer(other.m_nrow, other.m_ncol);
        }
        for (size_t i = 0; i < m_nrow; ++i) {
            for (size_t j = 0; j < m_ncol; ++j) {
                (*this)(i, j) = other(i, j);
            }
        }
        return *this;
    }

    Matrix & operator=(std::vector<double> const & vec)
    {
        if (size() != vec.size())
        {
            throw std::out_of_range("number of elements mismatch");
        }

        size_t k = 0;
        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                (*this)(i,j) = vec[k];
                ++k;
            }
        }

        return *this;
    }

    Matrix(Matrix && other)
      : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(0, 0);
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
    }

    double *val_addr() const {
        return &(this->m_buffer[0]);
    }

    
    Matrix & operator=(Matrix && other)
    {
        if (this == &other) { return *this; }
        reset_buffer(0, 0);
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
        return *this;
    }

    ~Matrix()
    {
        reset_buffer(0, 0);
    }


    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }

    size_t size() const { return m_nrow * m_ncol; }

    double buffer(size_t i) const {
        if (i < m_nrow * m_ncol) {
            return m_buffer[i];
        } else {
            return 0.0;
        }
    }
    
    std::vector<double> buffer_vector() const
    {
        std::vector<double> buffer;
        buffer.reserve(m_nrow * m_ncol);

        for (size_t i = 0; i < m_nrow; ++i) {
            for (size_t j = 0; j < m_ncol; ++j) {
                buffer.push_back(m_buffer[index(i, j)]);
            }
        }

        return buffer;
    }


    double getvalue(size_t row, size_t col) const {
        if (row < m_nrow && col < m_ncol) {
            return m_buffer[index(row, col)];
        } else {
            throw std::out_of_range("Index out of bounds");
        }
    }

    void setvalue(size_t row, size_t col, double value) {
        if (row < m_nrow && col < m_ncol) {
            m_buffer[index(row, col)] = value;
        } else {
            throw std::out_of_range("Index out of bounds");
        }
    }
     //operator overloading

    double & operator()(size_t row, size_t col)       { return m_buffer[index(row,col)]; }
    double   operator()(size_t row, size_t col) const { return m_buffer[index(row,col)]; }

    double & operator[](size_t idx)                   { return m_buffer[idx]; }
    double   operator[](size_t idx) const             { return m_buffer[idx]; }

    // Matrix compare 
    bool operator==(const Matrix& other) const {
        if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) {
            return false;
        }

        for (size_t i = 0; i < m_nrow; ++i) {
            for (size_t j = 0; j < m_ncol; ++j) {
                if (m_buffer[index(i, j)] != other.m_buffer[other.index(i, j)]) {
                    return false;
                }
            }
        }

        return true;
    }


private:

    size_t index(size_t row, size_t col) const
    {
        return row + col * m_nrow;
    }

    void reset_buffer(size_t nrow, size_t ncol)
    {
        if (m_buffer) { delete[] m_buffer; }
        const size_t nelement = nrow * ncol;
        if (nelement) { m_buffer = new double[nelement]; }
        else          { m_buffer = nullptr; }
        m_nrow = nrow;
        m_ncol = ncol;
    }

    size_t m_nrow = 0;
    size_t m_ncol = 0;
    double * m_buffer = nullptr;

};

// Basic matrix multiplication
Matrix operator*(Matrix const & mat1, Matrix const & mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i=0; i<ret.nrow(); ++i)
    {
        for (size_t k=0; k<ret.ncol(); ++k)
        {
            double v = 0;
            for (size_t j=0; j<mat1.ncol(); ++j)
            {
                v += mat1(i,j) * mat2(j,k);
            }
            ret(i,k) = v;
        }
    }

    return ret;
}
/*
 * Naive matrix matrix multiplication.
 */
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of the second matrix row");
    }

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i = 0; i < ret.nrow(); ++i)
    {
        for (size_t k = 0; k < ret.ncol(); ++k)
        {
            double v = 0;
            for (size_t j = 0; j < mat1.ncol(); ++j)
            {
                v += mat1(i, j) * mat2(j, k);
            }
            ret(i, k) = v;
        }
    }

    return ret;
}


std::ostream & operator << (std::ostream & ostr, Matrix const & mat)
{
    for (size_t i=0; i<mat.nrow(); ++i)
    {
        ostr << std::endl << " ";
        for (size_t j=0; j<mat.ncol(); ++j)
        {
            ostr << " " << std::setw(2) << mat(i, j);
        }
    }

    return ostr;
}

// Function for matrix-matrix multiplication with tiling
Matrix multiply_tile(const Matrix& mat1, const Matrix& mat2, size_t tileSize) {
    // store mat1 and mat2 to binary file
    std::ofstream mat1File("matrixMat1.bin", std::ios::out | std::ios::binary);
    mat1File.write((char*)mat1.val_addr(), mat1.nrow() * mat1.ncol() * sizeof(double));
    mat1File.close();

    std::ofstream mat2File("matrixMat2.bin", std::ios::out | std::ios::binary);
    mat2File.write((char*)mat2.val_addr(), mat2.nrow() * mat2.ncol() * sizeof(double));
    mat2File.close();

    // Load matrix mat1 and mat2
    Matrix loadedMat1(mat1.nrow(), mat1.ncol());
    std::ifstream mat1Infile("matrixMat1.bin", std::ios::in | std::ios::binary);
    mat1Infile.read((char*)loadedMat1.val_addr(), loadedMat1.nrow() * loadedMat1.ncol() * sizeof(double));
    mat1Infile.close();

    Matrix loadedMat2(mat2.nrow(), mat2.ncol());
    std::ifstream mat2Infile("matrixMat2.bin", std::ios::in | std::ios::binary);
    mat2Infile.read((char*)loadedMat2.val_addr(), loadedMat2.nrow() * loadedMat2.ncol() * sizeof(double));
    mat2Infile.close();

    size_t n = loadedMat1.nrow();
    size_t m = loadedMat1.ncol();
    size_t p = loadedMat2.ncol();

    if (m != loadedMat2.nrow()) {
        throw std::invalid_argument("Matrix dimensions are not compatible for multiplication.");
    }

    Matrix result(n, p);

    for (size_t i0 = 0; i0 < n; i0 += tileSize) {
        for (size_t j0 = 0; j0 < p; j0 += tileSize) {
            for (size_t k0 = 0; k0 < m; k0 += tileSize) {
                for (size_t i = i0; i < std::min(i0 + tileSize, n); ++i) {
                    for (size_t j = j0; j < std::min(j0 + tileSize, p); ++j) {
                        double v = 0;
                        for (size_t k = k0; k < std::min(k0 + tileSize, m); ++k) {
                            v += loadedMat1(i, k) * loadedMat2(k, j);
                        }
                        result(i, j) += v;
                    }
                }
            }
        }
    }

    return result;
}


Matrix multiply_mkl(const Matrix& mat1, const Matrix& mat2)
{
    // store mat1 and mat2 to binary file
    std::ofstream mat1File("matrixMat1.bin", std::ios::out | std::ios::binary);
    mat1File.write((char*)mat1.val_addr(), mat1.nrow() * mat1.ncol() * sizeof(double));
    mat1File.close();

    std::ofstream mat2File("matrixMat2.bin", std::ios::out | std::ios::binary);
    mat2File.write((char*)mat2.val_addr(), mat2.nrow() * mat2.ncol() * sizeof(double));
    mat2File.close();

    // Load matrix mat1 and mat2
    Matrix loadedMat1(mat1.nrow(), mat1.ncol());
    std::ifstream mat1Infile("matrixMat1.bin", std::ios::in | std::ios::binary);
    mat1Infile.read((char*)loadedMat1.val_addr(), loadedMat1.nrow() * loadedMat1.ncol() * sizeof(double));
    mat1Infile.close();

    Matrix loadedMat2(mat2.nrow(), mat2.ncol());
    std::ifstream mat2Infile("matrixMat2.bin", std::ios::in | std::ios::binary);
    mat2Infile.read((char*)loadedMat2.val_addr(), loadedMat2.nrow() * loadedMat2.ncol() * sizeof(double));
    mat2Infile.close();

    double alpha = 1.0; 
    double beta = 0.0;
    Matrix ret(loadedMat1.nrow(), loadedMat2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                loadedMat1.nrow(), loadedMat2.ncol(), loadedMat1.ncol(), alpha, 
                loadedMat1.val_addr(), loadedMat1.ncol(), loadedMat2.val_addr(), loadedMat2.ncol(), 
                beta, ret.val_addr(), loadedMat2.ncol());

    return ret;
}


int main(int argc, char ** argv)
{
    std::cout << ">>> Naive algo for A(2x3) times B(3x2):" << std::endl;
    Matrix mat1(2, 3, std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0});
    Matrix mat2(3, 2, std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0});
    std::cout << "matrix A (2x3):" << mat1 << std::endl;
    std::cout << "matrix B (3x2):" << mat2 << std::endl;
    Matrix mat3 = multiply_naive(mat1, mat2);
    std::cout << "result matrix C (2x2) = AB:" << mat3 << std::endl;

    std::cout << ">>> Tiling algo for A(2x3) times B(3x2):" << std::endl;
    Matrix mat4 = multiply_tile(mat1, mat2, 4);
    std::cout << "result matrix C (2x2) = AB:" << mat4 << std::endl;

    std::cout << ">>> DGEMM for A(2x3) times B(3x2):" << std::endl;
    Matrix mat5 = multiply_mkl(mat1, mat2);
    std::cout << "result matrix C (2x2) = AB:" << mat5 << std::endl;

    return 0;
}


namespace py = pybind11;

PYBIND11_MODULE(_matrix, m) {
    m.doc() = "Matrix Multiplication function unit test.";

    py::class_<Matrix>(m, "Matrix")
        .def(py::init<>())
        .def(py::init<size_t, size_t>())
        .def(py::init<size_t, size_t, std::vector<double>>())
        .def("buffer_vector", &Matrix::buffer_vector)
        .def("getvalue", &Matrix::getvalue, py::arg("row"), py::arg("col"))
        .def("setvalue", &Matrix::setvalue, py::arg("row"), py::arg("col"), py::arg("value"))
        .def("__getitem__", [](const Matrix &m_matrix, std::pair<size_t, size_t> index) {
            return m_matrix(index.first, index.second);
        })
        .def("__setitem__", [](Matrix &m_matrix, std::pair<size_t, size_t> index, double value) {
            m_matrix(index.first, index.second) = value;
        })
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def("__eq__", &Matrix::operator==);

    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
}




