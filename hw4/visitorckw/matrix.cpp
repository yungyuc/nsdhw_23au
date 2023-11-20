#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <algorithm>
#include <limits>
#include <mkl.h>
#include <cstdlib>

class ByteCounterImpl
{
public:
    size_t allocated = 0;
    size_t deallocated = 0;
    size_t refcount = 0;
};

class ByteCounter
{
public:
    ByteCounter()
        : m_impl(new ByteCounterImpl)
    {
        incref();
    }
    ByteCounter(ByteCounter const & other)
        : m_impl(other.m_impl)
    {
        incref();
    }
    ByteCounter & operator=(ByteCounter const & other)
    {
        if (&other != this)
        {
            decref();
            m_impl = other.m_impl;
            incref();
        }

        return *this;
    }
    ByteCounter(ByteCounter && other)
        : m_impl(other.m_impl)
    {
        incref();
    }
    ByteCounter & operator=(ByteCounter && other)
    {
        if (&other != this)
        {
            decref();
            m_impl = other.m_impl;
            incref();
        }

        return *this;
    }
    ~ByteCounter()
    {
        decref();
    }
    void swap(ByteCounter & other)
    {
        std::swap(m_impl, other.m_impl);
    }
    void increase(std::size_t amount)
    {
        m_impl->allocated += amount;
    }
    void decrease(std::size_t amount)
    {
        m_impl->deallocated += amount;
    }
    std::size_t bytes() const
    {
        return m_impl->allocated - m_impl->deallocated;
    }
    std::size_t allocated() const
    {
        return m_impl->allocated;
    }
    std::size_t deallocated() const
    {
        return m_impl->deallocated;
    }
    std::size_t refcount() const
    {
        return m_impl->refcount;
    }

private:
    void incref()
    {
        ++m_impl->refcount;
    }
    void decref()
    {
        if (nullptr == m_impl) {}
        else if (1 == m_impl->refcount)
        {
            delete m_impl;
            m_impl = nullptr;
        }
        else
        {
            --m_impl->refcount;
        }
    }
    ByteCounterImpl * m_impl;
};

ByteCounter counter;

template <class T>
struct MyAllocator
{
    using value_type = T;
    MyAllocator() = default;
    T * allocate(std::size_t n)
    {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
        {
            throw std::bad_alloc();
        }
        const std::size_t bytes = n * sizeof(T);
        T * p = static_cast<T *>(std::malloc(bytes));
        if (p)
        {
            counter.increase(bytes);
            return p;
        }
        else
        {
            throw std::bad_alloc();
        }
    }
    void deallocate(T * p, std::size_t n) noexcept
    {
        std::free(p);

        const std::size_t bytes = n * sizeof(T);
        counter.decrease(bytes);
    }
};

size_t bytes() { return counter.bytes(); }
size_t allocated() { return counter.allocated(); }
size_t deallocated() { return counter.deallocated(); }

class Matrix
{
public:
    Matrix(size_t row_num, size_t col_num)
    {
        this->row_num = row_num;
        this->col_num = col_num;
        buffer = std::vector<double, MyAllocator<double>>(row_num * col_num);
    }
    double * operator[](size_t row) const
    {
        // return &buffer[row * col_num];
        return (double *)buffer.data() + row * col_num;
    }
    double * operator[](size_t row)
    {
        // return &buffer[row * col_num];
        return buffer.data() + row * col_num;
    }
    size_t nrow() const
    {
        return row_num;
    }
    size_t ncol() const
    {
        return col_num;
    }
    std::vector<double, MyAllocator<double>> buffer;
    size_t row_num = 0;
    size_t col_num = 0;
};

bool operator==(Matrix const & mat_A, Matrix const & mat_B)
{
    if (mat_A.row_num != mat_B.row_num || mat_A.col_num != mat_B.col_num)
        return false;
    for (size_t i = 0; i < mat_A.row_num; ++i)
    {
        for (size_t j = 0; j < mat_A.col_num; ++j)
        {
            if (mat_A[i][j] != mat_B[i][j])
                return false;
        }
    }
    return true;
}

bool operator!=(Matrix const & mat_A, Matrix const & mat_B)
{
    return !(mat_A == mat_B);
}

Matrix multiply_naive(Matrix const & mat_A, Matrix const & mat_B)
{
    Matrix mat(mat_A.row_num, mat_B.col_num);

    for (size_t i = 0; i < mat_A.row_num; ++i)
    {
        for (size_t j = 0; j < mat_B.col_num; ++j)
        {
            mat[i][j] = 0;
            for (size_t k = 0; k < mat_A.col_num; ++k)
            {
                mat[i][j] += mat_A[i][k] * mat_B[k][j];
            }
        }
    }
    return mat;
}

Matrix multiply_tile(Matrix const & mat_A, Matrix const & mat_B, size_t tile_size)
{
    Matrix mat(mat_A.row_num, mat_B.col_num);

    for (size_t row = 0; row < mat_A.row_num; row += tile_size)
    {
        for (size_t col = 0; col < mat_B.col_num; col += tile_size)
        {
            for (size_t m = 0; m < mat_A.col_num; m += tile_size)
            {
                size_t i_end = std::min(mat_A.row_num,
                                        row + tile_size);
                size_t j_end = std::min(mat_B.col_num,
                                        col + tile_size);
                size_t k_end =
                    std::min(mat_A.col_num, m + tile_size);
                for (size_t i = row; i < i_end; ++i)
                {
                    for (size_t j = col; j < j_end; ++j)
                    {
                        for (size_t k = m; k < k_end;
                             ++k)
                        {
                            mat[i][j] +=
                                mat_A[i][k] *
                                mat_B[k][j];
                        }
                    }
                }
            }
        }
    }
    return mat;
}

Matrix multiply_mkl(Matrix const & mat_A, Matrix const & mat_B)
{
    Matrix mat(mat_A.row_num, mat_B.col_num);

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mat_A.row_num, mat_B.col_num, mat_A.col_num, 1.0, mat_A.buffer.data(), mat_A.col_num, mat_B.buffer.data(), mat_B.col_num, 0.0, mat.buffer.data(), mat.col_num);
    return mat;
}

namespace py = pybind11;

PYBIND11_MODULE(_matrix, m)
{
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_mkl", &multiply_mkl);
    m.def("multiply_tile", &multiply_tile);
    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<size_t, size_t>())
        .def("__setitem__",
             [](Matrix & self, std::pair<size_t, size_t> i, double val)
             {
                 self[i.first][i.second] = val;
             })
        .def("__getitem__",
             [](Matrix & self, std::pair<size_t, size_t> i)
             {
                 return self[i.first][i.second];
             })
        .def_property("nrow", &Matrix::nrow, nullptr)
        .def_property("ncol", &Matrix::ncol, nullptr)
        .def("__eq__", &operator==)
        .def("bytes", &bytes)
        .def("allocated", &allocated)
        .def("deallocated", &deallocated);
}
