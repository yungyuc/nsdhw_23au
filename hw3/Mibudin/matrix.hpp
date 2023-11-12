#pragma once
#ifndef matrix_HPP_
#define matrix_HPP_


#include<cstddef>
#include<algorithm>


class Matrix
{
public:
    inline Matrix(std::size_t nrow, std::size_t ncol)
        : m_nrow(nrow), m_ncol(ncol), m_buffer(new double[nrow * ncol]{}) {};
    inline bool operator==(const Matrix& rhs) const
    {
        if(m_nrow != rhs.m_nrow || m_ncol != rhs.m_ncol)
        {
            return false;
        }

        return std::equal(m_buffer, m_buffer + m_nrow * m_ncol, rhs.m_buffer);
    }
    inline const std::size_t& nrow() const
    {
        return m_nrow;
    }
    inline const std::size_t& ncol() const
    {
        return m_ncol;
    }
    inline double& operator()(std::size_t row, std::size_t col)
    {
        return m_buffer[idx(row, col)];
    }
    inline const double& operator()(std::size_t row, std::size_t col) const
    {
        return m_buffer[idx(row, col)];
    }
    inline double*& buffer()
    {
        return m_buffer;
    }
    inline const double* const& buffer() const
    {
        return m_buffer;
    }

private:
    inline std::size_t idx(std::size_t row, std::size_t col) const
    {
        return row * m_ncol + col;
    }

    std::size_t m_nrow = 0;
    std::size_t m_ncol = 0;
    double* m_buffer = nullptr;
};


#endif  // matrix_HPP_
