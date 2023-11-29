#pragma once
#ifndef matrix__matrix_op_HPP_
#define matrix__matrix_op_HPP_


#include"matrix.hpp"


namespace matrix
{
void validate_multiply(const Matrix& mat1, const Matrix& mat2);

Matrix multiply_naive(const Matrix& mat1, const Matrix& mat2);
Matrix multiply_tile(
    const Matrix& mat1, const Matrix& mat2, std::size_t tile_size);
Matrix multiply_mkl(const Matrix& mat1, const Matrix& mat2);

std::size_t bytes();
std::size_t allocated();
std::size_t deallocated();
}  // namespace matrix


#endif  // matrix__matrix_op_HPP_
