#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include "mkl_cblas.h"
#include "CustomAllocator.hpp"

CustomAllocator<double> allocator;

class Matrix {

    public:

        Matrix(size_t nrow, size_t ncol)
        : m_nrow(nrow), m_ncol(ncol)
        {
            // std::cout << ">> initialize" << std::endl;
            reset_buffer(nrow, ncol);
        }

        Matrix(size_t nrow, size_t ncol, std::vector<double> const & vec)
        : m_nrow(nrow), m_ncol(ncol)
        {
            // std::cout << ">> initialize with vector" << std::endl;
            reset_buffer(nrow, ncol);
            (*this) = vec;
        }

        Matrix & operator=(std::vector<double> const & vec)
        {
            // std::cout << ">> operator= with vector" << std::endl;
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
            // std::cout << ">> initialize, copy other to this" << std::endl;
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
            // std::cout << ">> operator= copy &other to *this" << std::endl;
            if (this == &other) {
                return *this;
            }
            if (m_nrow != other.m_nrow || m_ncol != other.m_ncol) {
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
            // std::cout << ">> initialize, swap other and this?" << std::endl;
            reset_buffer(0, 0);
            std::swap(m_nrow, other.m_nrow);
            std::swap(m_ncol, other.m_ncol);
            std::swap(m_buffer, other.m_buffer);
        }

        Matrix & operator=(Matrix && other)
        {
            // std::cout << ">>operator= swap && other" << std::endl;
            if (this == &other) {
                return *this;
            }
            reset_buffer(0, 0);
            std::swap(m_nrow, other.m_nrow);
            std::swap(m_ncol, other.m_ncol);
            std::swap(m_buffer, other.m_buffer);
            return *this;
        }

        ~Matrix()   // return, clear buffer
        {
            // std::cout << ">> ~Matrix" << std::endl;
            reset_buffer(0, 0);
        }

        double   operator() (size_t row, size_t col) const
        {
            // std::cout << ">> operator()" << std::endl;
            return m_buffer[index(row, col)];
        }
        double & operator() (size_t row, size_t col)
        {
            // std::cout << ">> & operator()" << std::endl;
            return m_buffer[index(row, col)];
        }

        bool operator== (Matrix const & mat2)
        {
            if ((m_ncol != mat2.ncol()) || (m_nrow != mat2.nrow()))
            {
                return false;
            }

            return std::equal(m_buffer.begin(), m_buffer.end(), mat2.buffer());
        }

        bool operator!= (Matrix const & mat2)
        {
            return !(*this == mat2);
        }

        size_t nrow() const {
            // std::cout << ">> nrow() = " << m_nrow << std::endl;
            return m_nrow;
        }
        size_t ncol() const {
            // std::cout << ">> ncol() = " << m_ncol << std::endl;
            return m_ncol;
        }

        size_t size() const {
            // std::cout << ">>size()" << std::endl;
            return m_nrow * m_ncol;
        }
        double  buffer(size_t i) const {
            // std::cout << ">>buffer(i)" << std::endl;
            return m_buffer[i];
        }
        double *buffer() {
            return m_buffer.data();
        }
        const double *buffer() const {
            return m_buffer.data();
        }

    private:

        size_t index(size_t row, size_t col) const
        {
            // std::cout << ">> index(size_t row, size_t col)" << std::endl;
            return row + col * m_nrow;
        }

        void reset_buffer(size_t nrow, size_t ncol)
        {
            // std::cout << ">> reset_buffer(size_t nrow, size_t ncol)" << std::endl;
            const size_t nelement = nrow * ncol;
            if (nelement) {
                m_buffer.resize(nelement);
            }

            m_nrow = nrow;
            m_ncol = ncol;
        }

        size_t m_nrow = 0;
        size_t m_ncol = 0;
        std::vector<double, CustomAllocator<double>> m_buffer = std::vector<double, CustomAllocator<double>>(allocator);

};


void validate_multiplication(Matrix const & mat1, Matrix const & mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }
}

// Naive matrix-matrix multiplication.
Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2)
{
    validate_multiplication(mat1, mat2);

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i=0; i<ret.nrow(); ++i)
    {
        for (size_t k=0; k<ret.ncol(); ++k)
        {
            double index_sum = 0;
            for (size_t j=0; j<mat1.ncol(); ++j)    // j<mat2.nrow()
            {
                // std::cout << i << j << k << std::endl;
                index_sum += mat1(i,j) * mat2(j,k);
            }
            ret(i,k) = index_sum;
        }
    }

    return ret;
}


Matrix multiply_mkl(Matrix const & mat1, Matrix const & mat2)
{
    validate_multiplication(mat1, mat2);

    Matrix ret(mat1.nrow(), mat2.ncol());

    cblas_dgemm(
        CblasRowMajor   /* const CBLAS_LAYOUT Layout */
      , CblasNoTrans    /* const CBLAS_TRANSPOSE transa */
      , CblasNoTrans    /* const CBLAS_TRANSPOSE transb */
      , mat1.nrow()     /* const MKL_INT m */
      , mat2.ncol()     /* const MKL_INT n */
      , mat1.ncol()     /* const MKL_INT k */
      , 1.0             /* const double alpha */
      , mat1.buffer()   /* const double *a */
      , mat1.ncol()     /* const MKL_INT lda */
      , mat2.buffer()   /* const double *b */
      , mat2.ncol()     /* const MKL_INT ldb */
      , 0.0             /* const double beta */
      , ret.buffer()    /* double * c */
      , ret.ncol()      /* const MKL_INT ldc */
    );

    return ret;
}

std::ostream & operator << (std::ostream & ostr, Matrix const & mat)
{
    // std::cout << "operator << (print matrix)" << std::endl;
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


int main(int argc, char ** argv)
{
    std::cout << ">>> A(2x3) times B(3x2):" << std::endl;
    Matrix mat1(2, 3, std::vector<double>{1, 2, 3, 4, 5, 6});
    Matrix mat2(3, 2, std::vector<double>{1, 2, 3, 4, 5, 6});
    std::cout << "allocator: bytes = " << allocator.counter.bytes();
    std::cout << ", allocated = " << allocator.counter.allocated();
    std::cout << ", deallocated = " << allocator.counter.deallocated() << std::endl;

    std::cout << "matrix A (2x3):" << mat1 << std::endl;
    std::cout << "matrix B (3x2):" << mat2 << std::endl;
    std::cout << "allocator: bytes = " << allocator.counter.bytes();
    std::cout << ", allocated = " << allocator.counter.allocated();
    std::cout << ", deallocated = " << allocator.counter.deallocated() << std::endl;

    Matrix ret_naive = multiply_naive(mat1, mat2);
    std::cout << "multiply_naive result matrix C (2x2) = AB:" << ret_naive << std::endl;
    std::cout << "allocator: bytes = " << allocator.counter.bytes();
    std::cout << ", allocated = " << allocator.counter.allocated();
    std::cout << ", deallocated = " << allocator.counter.deallocated() << std::endl;

    Matrix ret_mkl = multiply_mkl(mat1, mat2);
    std::cout << "multiply_mkl result matrix C (2x2) = AB:" << ret_mkl << std::endl;
    std::cout << "allocator: bytes = " << allocator.counter.bytes();
    std::cout << ", allocated = " << allocator.counter.allocated();
    std::cout << ", deallocated = " << allocator.counter.deallocated() << std::endl;

    return 0;
}


PYBIND11_MODULE(_matrix, m) {   // module name
    m.doc() = "Matrix-Matrix Multiplication.";

    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def(pybind11::init<size_t, size_t, std::vector<double> const & >())
        .def("__getitem__",
            [](const Matrix& mat, std::pair<size_t, size_t> index) {
                return mat(index.first, index.second);
            }
        )
        .def("__setitem__",
            [](Matrix& mat, std::pair<size_t, size_t> index, double value) {
                mat(index.first, index.second) = value;
            }
        )
        .def("__eq__", &Matrix::operator==)
        .def("__ne__", &Matrix::operator!=)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol);

    m.def("multiply_naive", &multiply_naive, pybind11::arg("mat1"), pybind11::arg("mat2"));
    m.def("multiply_mkl", &multiply_mkl, pybind11::arg("mat1"), pybind11::arg("mat2"));
    
    m.def("bytes", []() {
        return allocator.counter.bytes();
    });
    m.def("allocated", []() {
        return allocator.counter.allocated();
    });
    m.def("deallocated", []() {
        return allocator.counter.deallocated();
    });
}