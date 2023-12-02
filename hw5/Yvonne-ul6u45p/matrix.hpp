#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <cmath>
#include "mkl_cblas.h"

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

    bool operator== (Matrix const & mat2) const
    {
        if ((m_ncol != mat2.ncol()) || (m_nrow != mat2.ncol()))
        {
            return false;
        }

        for (size_t i=0; i<m_nrow; ++i)
        {
            for (size_t j=0; j<m_ncol; ++j)
            {
                if (m_buffer[index(i, j)] != mat2.m_buffer[mat2.index(i, j)])
                {
                    return false;
                }
            }
        }

        return true;
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
    double buffer(size_t i) const {
        // std::cout << ">>buffer(i)" << std::endl;
        return m_buffer[i];
    }
    double &buffer(size_t i) {
        // std::cout << ">>buffer(i)" << std::endl;
        return m_buffer[i];
    }
    double *buffer() const {
        return m_buffer;
    }
    std::vector<double> buffer_vector() const
    {
        // std::cout << ">>buffer_vector()" << std::endl;
        return std::vector<double>(m_buffer, m_buffer+size());
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
        if (m_buffer) {
            delete[] m_buffer;
        }
        const size_t nelement = nrow * ncol;
        if (nelement) {
            m_buffer = new double[nelement]();
        }
        else {
            m_buffer = nullptr;
        }
        m_nrow = nrow;
        m_ncol = ncol;
    }

    size_t m_nrow = 0;
    size_t m_ncol = 0;
    double * m_buffer = nullptr;

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

// Tiled matrix matrix multiplication.
Matrix multiply_tile(Matrix const & mat1, Matrix const & mat2, size_t const tsize)
{
    validate_multiplication(mat1, mat2);

    Matrix ret(mat1.nrow(), mat2.ncol());

    // const size_t ntrow1 = std::ceil(mat1.nrow() / tsize);
    // const size_t ntcol1 = std::ceil(mat1.ncol() / tsize);
    // const size_t ntrow2 = std::ceil(mat2.nrow() / tsize);
    // const size_t ntcol2 = std::ceil(mat2.ncol() / tsize);
    // cout << ntrow1 << " x " << ntcol1 << ", " << ntrow1 << " x " << ntcol2  << endl;

    for (size_t ti_row=0; ti_row<mat1.nrow(); ti_row+=tsize)
    {
        for (size_t ti_col=0; ti_col<mat2.ncol(); ti_col+=tsize)
        {
            for (size_t ti_j=0; ti_j<mat1.ncol(); ti_j+=tsize)
            {
                // within a tile
                size_t tr_end = std::min(mat1.nrow(), ti_row + tsize);
                size_t tc_end = std::min(mat2.ncol(), ti_col + tsize);
                size_t tj_end = std::min(mat1.ncol(), ti_j   + tsize);
                // std::cout << ti_row << " " << ti_j << " " << ti_col << ", " << tr_end << " " << tj_end << " " << tc_end << std::endl;
                
                for (size_t i=ti_row; i<tr_end; ++i)
                {
                    for (size_t k=ti_col; k<tc_end; ++k)
                    {
                        for (size_t j=ti_j; j<tj_end; ++j)    // j<mat2.nrow()
                        {
                            // std::cout << ret(i,k) << " " << i << j << k << " " << mat1(i,j) << " * " << mat2(j,k) << std::endl;
                            ret(i,k) += mat1(i,j) * mat2(j,k);
                        }
                    }
                }
            }
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
