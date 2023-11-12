#pragma once
#ifndef _matrix_HPP_
#define _matrix_HPP_


#include"matrix.hpp"


void validate_multiply(const Matrix& mat1, const Matrix& mat2);
Matrix multiply_naive(const Matrix& mat1, const Matrix& mat2);
Matrix multiply_tile(
    const Matrix& mat1, const Matrix& mat2, std::size_t tile_size);
Matrix multiply_mkl(const Matrix& mat1, const Matrix& mat2);


#endif  // _matrix_HPP_
