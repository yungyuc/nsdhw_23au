#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include "_allocator.hpp"
#include <vector>
#include <utility>
#include <mkl.h>

static CustomAllocator<double> MyAllocator;
inline size_t bytes() { return MyAllocator.counter.bytes(); }
inline size_t allocated() { return MyAllocator.counter.allocated(); }
inline size_t deallocated() { return MyAllocator.counter.deallocated(); }

class Matrix
{

public:
    Matrix(size_t row, size_t col) : m_nrow(row), m_ncol(col), m_buffer(MyAllocator) {
        m_buffer.resize(row * col);
    }

    Matrix(Matrix const &mat) : m_nrow(mat.nrow()), m_ncol(mat.ncol()), m_buffer(mat.m_buffer, MyAllocator) {}
    bool operator==(Matrix const &mat2) const
    {
        if (m_ncol != mat2.ncol() || m_nrow != mat2.ncol())
            return false;

        for (size_t i = 0; i < m_nrow; i++)
        {
            for (size_t j = 0; j < m_ncol; j++)
            {
                if (m_buffer[i * m_ncol + j] != mat2(i, j))
                    return false;
            }
        }
        return true;
    }
    double operator()(size_t row, size_t col) const { return m_buffer[row*m_ncol + col]; }
    double &operator()(size_t row, size_t col) { return m_buffer[row*m_ncol + col]; }

    double *data() { return m_buffer.data(); }
    double const *data() const { return m_buffer.data(); }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }

private:
    size_t m_nrow;
    size_t m_ncol;
    std::vector<double, CustomAllocator<double>> m_buffer;
};


Matrix multiply_tile(Matrix const& mat1, Matrix const& mat2, size_t tsize);
Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2);
Matrix multiply_mkl(Matrix const& mat1, Matrix const& mat2);

#endif