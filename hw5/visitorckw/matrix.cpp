#include "matrix.hpp"

bool operator==(Matrix const &mat_A, Matrix const &mat_B)
{
	if (mat_A.row_num != mat_B.row_num || mat_A.col_num != mat_B.col_num)
		return false;
	for (size_t i = 0; i < mat_A.row_num; ++i) {
		for (size_t j = 0; j < mat_A.col_num; ++j) {
			if (mat_A[i][j] != mat_B[i][j])
				return false;
		}
	}
	return true;
}

bool operator!=(Matrix const &mat_A, Matrix const &mat_B)
{
	return !(mat_A == mat_B);
}

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
			for (size_t m = 0; m < mat_A.col_num; m += tile_size) {
				size_t i_end = std::min(mat_A.row_num,
							row + tile_size);
				size_t j_end = std::min(mat_B.col_num,
							col + tile_size);
				size_t k_end =
					std::min(mat_A.col_num, m + tile_size);
				for (size_t i = row; i < i_end; ++i) {
					for (size_t j = col; j < j_end; ++j) {
						for (size_t k = m; k < k_end;
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