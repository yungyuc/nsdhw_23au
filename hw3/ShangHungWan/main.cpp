#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <cblas.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

class Matrix
{
public:
    double *m_buffer = nullptr;
    size_t m_nrow = 0;
    size_t m_ncol = 0;

    Matrix(size_t nrow, size_t ncol)
        : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
    }

    Matrix(size_t nrow, size_t ncol, std::vector<double> const &vec)
        : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
        (*this) = vec;
    }

    Matrix &operator=(std::vector<double> const &vec)
    {
        if (size() != vec.size())
        {
            throw std::out_of_range("number of elements mismatch");
        }

        size_t k = 0;
        for (size_t i = 0; i < m_nrow; ++i)
        {
            for (size_t j = 0; j < m_ncol; ++j)
            {
                (*this)(i, j) = vec[k];
                ++k;
            }
        }

        return *this;
    }

    Matrix(Matrix const &other)
        : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(other.m_nrow, other.m_ncol);
        for (size_t i = 0; i < m_nrow; ++i)
        {
            for (size_t j = 0; j < m_ncol; ++j)
            {
                (*this)(i, j) = other(i, j);
            }
        }
    }

    Matrix &operator=(Matrix const &other)
    {
        if (this == &other)
        {
            return *this;
        }
        if (m_nrow != other.m_nrow || m_ncol != other.m_ncol)
        {
            reset_buffer(other.m_nrow, other.m_ncol);
        }
        for (size_t i = 0; i < m_nrow; ++i)
        {
            for (size_t j = 0; j < m_ncol; ++j)
            {
                (*this)(i, j) = other(i, j);
            }
        }
        return *this;
    }

    Matrix(Matrix &&other)
        : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(0, 0);
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
    }

    Matrix &operator=(Matrix &&other)
    {
        if (this == &other)
        {
            return *this;
        }
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

    double operator()(size_t row, size_t col) const
    {
        return m_buffer[index(row, col)];
    }
    double &operator()(size_t row, size_t col)
    {
        return m_buffer[index(row, col)];
    }

    double operator[](size_t idx) const { return m_buffer[idx]; }
    double &operator[](size_t idx) { return m_buffer[idx]; }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }

    size_t size() const { return m_nrow * m_ncol; }
    double buffer(size_t i) const { return m_buffer[i]; }
    std::vector<double> buffer_vector() const
    {
        return std::vector<double>(m_buffer, m_buffer + size());
    }

    size_t index(size_t row, size_t col) const
    {
        return row + col * m_nrow;
    }

    void reset_buffer(size_t nrow, size_t ncol)
    {
        if (m_buffer)
        {
            delete[] m_buffer;
        }
        const size_t nelement = nrow * ncol;
        if (nelement)
        {
            m_buffer = new double[nelement];
        }
        else
        {
            m_buffer = nullptr;
        }
        m_nrow = nrow;
        m_ncol = ncol;
    }
};

bool operator==(Matrix const &mat1, Matrix const &mat2)
{
    if ((mat1.ncol() != mat2.ncol()) && (mat1.nrow() != mat2.ncol()))
    {
        return false;
    }

    for (size_t i = 0; i < mat1.nrow(); ++i)
    {
        for (size_t j = 0; j < mat1.ncol(); ++j)
        {
            if (mat1(i, j) != mat2(i, j))
            {
                return false;
            }
        }
    }

    return true;
}

bool operator!=(Matrix const &mat1, Matrix const &mat2)
{
    return !(mat1 == mat2);
}

/*
 * Throw an exception if the shapes of the two matrices don't support
 * multiplication.
 */
void validate_multiplication(Matrix const &mat1, Matrix const &mat2)
{
    if (mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }
}

/*
 * Naive matrix matrix multiplication.
 */
Matrix operator*(Matrix const &mat1, Matrix const &mat2)
{
    validate_multiplication(mat1, mat2);

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

Matrix multiply_naive(Matrix const &mat1, Matrix const &mat2)
{
    return mat1 * mat2;
}

Matrix multiply_mkl(Matrix const &mat1, Matrix const &mat2)
{
    validate_multiplication(mat1, mat2);

    Matrix ret(mat1.nrow(), mat2.ncol());

    cblas_dgemm(
        CblasRowMajor, /* const CBLAS_LAYOUT Layout */
        CblasNoTrans,  /* const CBLAS_TRANSPOSE transa */
        CblasNoTrans,  /* const CBLAS_TRANSPOSE transb */
        mat1.nrow(),   /* const MKL_INT m */
        mat2.ncol(),   /* const MKL_INT n */
        mat1.ncol(),   /* const MKL_INT k */
        1.0,           /* const double alpha */
        mat1.m_buffer, /* const double *a */
        mat1.ncol(),   /* const MKL_INT lda */
        mat2.m_buffer, /* const double *b */
        mat2.ncol(),   /* const MKL_INT ldb */
        0.0,           /* const double beta */
        ret.m_buffer,  /* double * c */
        ret.ncol()     /* const MKL_INT ldc */
    );

    return ret;
}

/*
 * Tiled matrix matrix multiplication.
 */
Matrix multiply_tile(Matrix const &mat1, Matrix const &mat2, size_t block_size)
{
    if (block_size <= 0)
    {
        throw std::out_of_range("tile size must be positive");
    }

    validate_multiplication(mat1, mat2);

    const size_t nrow1 = mat1.nrow();
    const size_t ncol1 = mat1.ncol();
    const size_t ncol2 = mat2.ncol();

    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i = 0; i < nrow1; i++)
        for (size_t j = 0; j < ncol2; j++)
            ret(i, j) = 0;

    for (size_t i = 0; i < nrow1; i += block_size)
        for (size_t j = 0; j < ncol2; j += block_size)
            for (size_t l = 0; l < ncol1; l += block_size)
                for (size_t ii = i; ii < i + block_size && ii < nrow1; ii++)
                    for (size_t jj = j; jj < j + block_size && jj < ncol2; jj++)
                        for (size_t ll = l; ll < l + block_size && ll < ncol1; ll++)
                            ret(ii, jj) += mat1(ii, ll) * mat2(ll, jj);

    return ret;
}

PYBIND11_MODULE(_matrix, m)
{
    m.doc() = "ShangHungWan's hw3, matrix-matrix multiplication functions";

    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def(pybind11::self == pybind11::self)
        .def(pybind11::self != pybind11::self)
        .def("__getitem__", [](Matrix &mat, std::pair<size_t, size_t> index) -> double
             { return mat(index.first, index.second); })
        .def("__setitem__", [](Matrix &mat, std::pair<size_t, size_t> index, double val)
             { mat(index.first, index.second) = val; })
        .def_property("nrow", &Matrix::nrow, nullptr)
        .def_property("ncol", &Matrix::ncol, nullptr);
    m.def("multiply_naive", &multiply_naive, "matrix-matrix multiplication with native method");
    m.def("multiply_mkl", &multiply_mkl, "matrix-matrix multiplication with MKL method");
    m.def("multiply_tile", &multiply_tile, "matrix-matrix multiplication with tiling method");
}