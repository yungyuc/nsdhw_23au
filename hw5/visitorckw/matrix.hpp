#pragma once

#include <mkl.h>
#include <cstdlib>
#include <algorithm>
#include <new>

class Matrix {
    public:
	Matrix(size_t row_num, size_t col_num)
	{
		this->row_num = row_num;
		this->col_num = col_num;
		double *new_buffer = (double *)realloc(
			buffer, row_num * col_num * sizeof(double));
		if (!new_buffer) {
			free(buffer);
			buffer = NULL;
			throw std::bad_alloc();
		}
		buffer = new_buffer;
	}
	double *operator[](size_t row) const
	{
		return &buffer[row * col_num];
	}
	double *operator[](size_t row)
	{
		return &buffer[row * col_num];
	}
    double operator()(size_t row, size_t col) const {
        return buffer[row * col_num];
    }
    double &operator()(size_t row, size_t col) {
        return buffer[row * col_num];
    }
	size_t nrow() const
	{
		return row_num;
	}
	size_t ncol() const
	{
		return col_num;
	}
    double *data() { return &buffer[0]; }
	double *buffer = NULL;
	size_t row_num = 0;
	size_t col_num = 0;
};

bool operator==(Matrix const &mat_A, Matrix const &mat_B);
bool operator!=(Matrix const &mat_A, Matrix const &mat_B);
Matrix multiply_naive(Matrix const &mat_A, Matrix const &mat_B);
Matrix multiply_tile(Matrix const &mat_A, Matrix const &mat_B, size_t tile_size);
Matrix multiply_mkl(Matrix const &mat_A, Matrix const &mat_B);
