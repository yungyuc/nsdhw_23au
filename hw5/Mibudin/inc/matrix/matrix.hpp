#pragma once
#ifndef matrix__matrix_HPP_
#define matrix__matrix_HPP_


#include<cstddef>
#include<algorithm>
#include<vector>

#include"matrix/stl.hpp"


namespace matrix
{
class Matrix
{
public:
    using buffer_type = std::vector<double, CustomAllocator<double>>;

    inline Matrix(std::size_t nrow, std::size_t ncol)
        : m_nrow(nrow), m_ncol(ncol), m_buffer(nrow * ncol) {};

    inline bool operator==(const Matrix& rhs) const
    {
        if(m_nrow != rhs.m_nrow || m_ncol != rhs.m_ncol)
        {
            return false;
        }

        return m_buffer == rhs.m_buffer;
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
        return m_buffer.at(idx(row, col));
    }

    inline const double& operator()(std::size_t row, std::size_t col) const
    {
        return m_buffer.at(idx(row, col));
    }

    inline buffer_type& buffer()
    {
        return m_buffer;
    }

    inline const buffer_type& buffer() const
    {
        return m_buffer;
    }

    inline double* data()
    {
        return m_buffer.data();
    }

    inline const double* data() const
    {
        return m_buffer.data();
    }

private:
    inline std::size_t idx(std::size_t row, std::size_t col) const
    {
        return row * m_ncol + col;
    }

    std::size_t m_nrow = 0;
    std::size_t m_ncol = 0;
    buffer_type m_buffer;
};
}  // namespace matrix


#endif  // matrix__matrix_HPP_
