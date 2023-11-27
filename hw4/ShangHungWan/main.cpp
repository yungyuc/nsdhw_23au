#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include <limits>
#include <vector>
#include <stdexcept>
#include <stdlib.h>
#include <cblas.h>

#include "includes/ByteCounter.h"

ByteCounter global_counter;

template <class T>
struct MyAllocator
{
    using value_type = T;

    MyAllocator() = default;

    template <class U>
    MyAllocator(const MyAllocator<U> &other) noexcept
    {
        counter = other.counter;
    }

    T *allocate(std::size_t n)
    {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
        {
            throw std::bad_alloc();
        }
        const std::size_t bytes = n * sizeof(T);
        T *p = static_cast<T *>(std::malloc(bytes));
        if (p)
        {
            global_counter.increase(bytes);
            counter.increase(bytes);
            return p;
        }
        else
        {
            throw std::bad_alloc();
        }
    }

    void deallocate(T *p, std::size_t n) noexcept
    {
        std::free(p);

        const std::size_t bytes = n * sizeof(T);
        global_counter.decrease(bytes);
        counter.decrease(bytes);
    }

    ByteCounter counter;
};

class Matrix
{
public:
    std::vector<double, MyAllocator<double>> m_buffer;
    size_t m_nrow = 0;
    size_t m_ncol = 0;

    Matrix(size_t nrow, size_t ncol) : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
    }

    Matrix(size_t nrow, size_t ncol, std::vector<double> const &vec) : m_nrow(nrow), m_ncol(ncol)
    {
        reset_buffer(nrow, ncol);
        (*this) = vec;
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

    Matrix(Matrix &&other)
        : m_nrow(other.m_nrow), m_ncol(other.m_ncol)
    {
        reset_buffer(0, 0);
        std::swap(m_nrow, other.m_nrow);
        std::swap(m_ncol, other.m_ncol);
        std::swap(m_buffer, other.m_buffer);
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

    size_t index(size_t row, size_t col) const
    {
        return row + col * m_nrow;
    }

    void reset_buffer(size_t nrow, size_t ncol)
    {
        if (m_buffer.size() > 0)
        {
            m_buffer.clear();
        }
        const size_t nelement = nrow * ncol;
        m_buffer.resize(nelement);
        m_nrow = nrow;
        m_ncol = ncol;
    }
};

template <class T, class U>
bool operator==(const MyAllocator<T> &a, const MyAllocator<U> &b)
{
    return a.counter == b.counter;
}

template <class T, class U>
bool operator!=(const MyAllocator<T> &a, const MyAllocator<U> &b)
{
    return !(a == b);
}

std::size_t bytes() { return global_counter.bytes(); }
std::size_t allocated() { return global_counter.allocated(); }
std::size_t deallocated() { return global_counter.deallocated(); }

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

    double *buffer1 = new double[mat1.m_buffer.size()];
    double *buffer2 = new double[mat2.m_buffer.size()];
    double *buffer_ret = new double[ret.m_buffer.size()];

    std::copy(mat1.m_buffer.begin(), mat1.m_buffer.end(), buffer1);
    std::copy(mat2.m_buffer.begin(), mat2.m_buffer.end(), buffer2);

    cblas_dgemm(
        CblasRowMajor, /* const CBLAS_LAYOUT Layout */
        CblasNoTrans,  /* const CBLAS_TRANSPOSE transa */
        CblasNoTrans,  /* const CBLAS_TRANSPOSE transb */
        mat1.nrow(),   /* const MKL_INT m */
        mat2.ncol(),   /* const MKL_INT n */
        mat1.ncol(),   /* const MKL_INT k */
        1.0,           /* const double alpha */
        buffer1,       /* const double *a */
        mat1.ncol(),   /* const MKL_INT lda */
        buffer2,       /* const double *b */
        mat2.ncol(),   /* const MKL_INT ldb */
        0.0,           /* const double beta */
        buffer_ret,    /* double * c */
        ret.ncol()     /* const MKL_INT ldc */
    );

    for (size_t i = 0; i < ret.nrow(); ++i)
    {
        for (size_t j = 0; j < ret.ncol(); ++j)
        {
            ret(i, j) = buffer_ret[i + j * ret.nrow()];
        }
    }
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

    m.def("bytes", &bytes, "number of bytes allocated");
    m.def("allocated", &allocated, "number of bytes allocated");
    m.def("deallocated", &deallocated, "number of bytes deallocated");
}