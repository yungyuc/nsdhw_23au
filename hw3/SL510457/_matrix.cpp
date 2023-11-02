#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <mkl/mkl.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>

namespace py=pybind11;
using namespace std;

class Matrix {

public:

    Matrix(size_t nrow, size_t ncol)
      : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
    }

    Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec)
      : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
        (*this) = vec;
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

    Matrix(Matrix const & other)
      : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(other.m_nrow, other.m_ncol);
        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                (*this)(i,j) = other(i,j);
            }
        }
    }

    Matrix & operator=(Matrix const & other)
    {
        if (this == &other) { return *this; }
        if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
        {
            reset_buffer(other.m_nrow, other.m_ncol);
        }
        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                (*this)(i,j) = other(i,j);
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

    double   operator() (size_t row, size_t col) const
    {
        return m_buffer[index(row, col)];
    }
    double & operator() (size_t row, size_t col)
    {
        return m_buffer[index(row, col)];
    }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }

    size_t size() const { return m_nrow * m_ncol; }
    double buffer(size_t i) const { return m_buffer[i]; }
    std::vector<double> buffer_vector() const
    {
        return std::vector<double>(m_buffer, m_buffer+size());
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

/*
 * Naive matrix matrix multiplication.
 */
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2)
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

//new
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, int blockSize) {
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    int n = mat1.nrow();
    int m = mat1.ncol();
    int p = mat2.ncol();

    Matrix ret(n, p);

    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < p; j += blockSize) {
            for (int k = 0; k < m; k += blockSize) {
                for (int ii = i; ii < std::min(i + blockSize, n); ++ii) {
                    for (int jj = j; jj < std::min(j + blockSize, p); ++jj) {
                        for (int kk = k; kk < std::min(k + blockSize, m); ++kk) {
                            ret(ii, jj) += mat1(ii, kk) * mat2(kk, jj);
                        }
                    }
                }
            }
        }
    }

    return ret;
}

Matrix multiply_mkl(Matrix const &m1, Matrix const &m2){
    mkl_set_num_threads(1);
    Matrix ret(m1.nrow(), m2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m1.nrow(),  m2.ncol(), m1.ncol(), 1.0 , m1.data(),
     m1.ncol(), m2.data(), m2.ncol(), 0.0, ret.data(), ret.ncol());
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

// int main(int argc, char ** argv)
// {
//     std::cout << ">>> A(2x3) times B(3x2):" << std::endl;
//     Matrix mat1(2, 3, std::vector<double>{1, 2, 3, 4, 5, 6});
//     Matrix mat2(3, 2, std::vector<double>{1, 2, 3, 4, 5, 6});

//     Matrix mat3 = multiply_tile(mat1,mat2,2);

//     std::cout << "matrix A (2x3):" << mat1 << std::endl;
//     std::cout << "matrix B (3x2):" << mat2 << std::endl;
//     std::cout << "result matrix C (2x2) = AB:" << mat3 << std::endl;

//     std::cout << ">>> B(3x2) times A(2x3):" << std::endl;
//     Matrix mat4 = multiply_tile(mat2,mat1,2);
//     std::cout << "matrix B (3x2):" << mat2 << std::endl;
//     std::cout << "matrix A (2x3):" << mat1 << std::endl;
//     std::cout << "result matrix D (3x3) = BA:" << mat4 << std::endl;

//     return 0;
// }

// PYBIND11_MODULE(_matrix, m)
// {
//     m.doc() = "Matrix-multiplication function test and performance.";
//     m.def("multiply_naive", &multiply_naive);
//     m.def("multiply_tile", &multiply_tile);
//     m.def("multiply_mkl", &multiply_mkl);

//     py::class_<Matrix>(m, "Matrix")
//         .def(py::init<>())
//         .def(py::init<size_t, size_t>())
//         .def(py::self == py::self)
//         .def_property_readonly("nrow", &Matrix::nrow)
//         .def_property_readonly("ncol", &Matrix::ncol)
//         .def("__getitem__", &Matrix::getvalue)
//         .def("__setitem__", &Matrix::setvalue);
// }


PYBIND11_MODULE(_matrix, m) {

    m.doc() = "matrix-matrix multiplication";
    m.def("multiply_naive", &multiply_naive, "naive");
    m.def("multiply_tile", &multiply_tile, "tile");
    m.def("multiply_mkl", &multiply_mkl, "mkl");

    py::class_<Matrix>(m, "Matrix")
        .def(py::init<int, int>())
        .def_property_readonly("nrow", [](const Matrix &mat) { return mat.nrow(); })
        .def_property_readonly("ncol", [](const Matrix &mat) { return mat.ncol(); })
        .def("__eq__", [](const Matrix &a, const Matrix &b) { 
            return a == b; })
        .def("__setitem__", [](Matrix &self, std::pair<int, int> idx, double val) {
            self(idx.first, idx.second) = val;
        })
        .def("__getitem__", [](const Matrix &self, std::pair<int, int> idx) {
            return self(idx.first, idx.second);
        });
}