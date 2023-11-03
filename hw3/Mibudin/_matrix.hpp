#pragma once
#ifndef _matrix_HPP_
#define _matrix_HPP_


#include<cstddef>


class Matrix
{
public:
    Matrix(std::size_t nrow, std::size_t ncol);
    bool operator==(const Matrix& rhs) const;

private:
    std::size_t m_nrow = 0;
    std::size_t m_ncol = 0;
    double* m_buffer = nullptr;
};


#endif  // _matrix_HPP_
