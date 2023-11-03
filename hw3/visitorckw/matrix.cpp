#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <mkl.h>
#include <cstdlib>

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
	double *buffer = NULL;
	size_t row_num = 0;
	size_t col_num = 0;
};

Matrix multiply_naive(Matrix const &mat_A, Matrix const &mat_B)
{
	Matrix mat(mat_A.row_num, mat_B.col_num);

	for (size_t i = 0; i < mat_A.row_num; ++i) {
		for (size_t j = 0; j < mat_B.col_num; ++j) {
			mat[i][j] = 0;
			for (size_t k = 0; k < mat_A.col_num; ++k) {
				mat[i][j] += mat_A[i][k] * mat_B[k][j];
			}
		}
	}
	return mat;
}

Matrix multiply_tile(Matrix const &mat_A, Matrix const &mat_B, size_t tile_size)
{
	Matrix mat(mat_A.row_num, mat_B.col_num);

	for (size_t row = 0; row < mat_A.row_num; row += tile_size) {
		for (size_t col = 0; col < mat_B.col_num; col += tile_size) {
			for (size_t inner = 0; inner < mat_A.col_num;
			     inner += tile_size) {
				for (size_t i = row;
				     i <
				     std::min(mat_A.row_num, row + tile_size);
				     ++i) {
					for (size_t j = col;
					     j < std::min(mat_B.col_num,
							  col + tile_size);
					     ++j) {
						mat[i][j] = 0;
						for (size_t k = inner;
						     k <
						     std::min(mat_A.col_num,
							      inner + tile_size);
						     ++k) {
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

Matrix multiply_mkl(Matrix const &mat_A, Matrix const &mat_B)
{
	Matrix mat(mat_A.row_num, mat_B.col_num);

	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mat_A.row_num,
		    mat_B.col_num, mat_A.col_num, 1.0, mat_A.buffer,
		    mat_A.col_num, mat_B.buffer, mat_B.col_num, 0.0, mat.buffer,
		    mat.col_num);
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
		     [](Matrix &self, std::pair<size_t, size_t> i, double val) {
			     self[i.first][i.second] = val;
		     })
		.def("__getitem__",
		     [](Matrix &self, std::pair<size_t, size_t> i) {
			     return self[i.first][i.second];
		     });
}
