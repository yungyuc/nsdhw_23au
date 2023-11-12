import math
import numpy as np
from _matrix import *


class TestHelper:
    @staticmethod
    def gen_fill_matrix_np(nrow, ncol) -> np.ndarray:
        return np.arange(nrow * ncol, dtype="float64").reshape(nrow, ncol)

    @staticmethod
    def fill_matrix(mat: Matrix) -> None:
        for i in range(mat.nrow):
            for j in range(mat.ncol):
                mat[i, j] = i * mat.ncol + j

    @staticmethod
    def closely_eq(mat1: Matrix, mat2: np.ndarray) -> bool:
        if (mat1.nrow, mat1.ncol) != mat2.shape:
            return False
        for i in range(mat1.nrow):
            for j in range(mat1.ncol):
                if not math.isclose(mat1[i, j], mat2[i, j]):
                    return False
        return True


class TestMatrixBasics:
    def test_constructing(self) -> None:
        nrow, ncol = 3, 4
        mat = Matrix(nrow, ncol)
        assert mat.nrow == nrow
        assert mat.ncol == ncol

        nrow, ncol = 7, 1
        mat = Matrix(nrow, ncol)
        assert mat.nrow == nrow
        assert mat.ncol == ncol

        nrow, ncol = 1024, 1024
        mat = Matrix(nrow, ncol)
        assert mat.nrow == nrow
        assert mat.ncol == ncol

    def test_value_accessing(self) -> None:
        mat1 = Matrix(3, 4)
        assert mat1[2, 3] == 0
        mat1[2, 3] = -1
        assert mat1[2, 3] == -1
        TestHelper.fill_matrix(mat1)
        assert mat1[2, 3] == 2 * mat1.ncol + 3

    def test_basic_operations(self) -> None:
        mat1 = Matrix(3, 4)
        mat2 = Matrix(3, 4)
        TestHelper.fill_matrix(mat1)
        TestHelper.fill_matrix(mat2)

        assert mat1 == mat2
        mat2[2, 3] = -1
        assert not (mat1 == mat2)


class TestMatrixMultiply:
    def test_multiply_naive(self) -> None:
        nrow, ncol = 512, 512

        mat1 = Matrix(nrow, ncol)
        mat2 = Matrix(nrow, ncol)
        TestHelper.fill_matrix(mat1)
        TestHelper.fill_matrix(mat2)
        ret = multiply_naive(mat1, mat2)

        mat1_np = TestHelper.gen_fill_matrix_np(nrow, ncol)
        mat2_np = TestHelper.gen_fill_matrix_np(nrow, ncol)
        ret_np = np.matmul(mat1_np, mat2_np)

        assert TestHelper.closely_eq(ret, ret_np)

    def test_multiply_tile(self) -> None:
        tile_size = 16
        nrow, ncol = 512, 512

        mat1 = Matrix(nrow, ncol)
        mat2 = Matrix(nrow, ncol)
        TestHelper.fill_matrix(mat1)
        TestHelper.fill_matrix(mat2)
        ret = multiply_tile(mat1, mat2, tile_size)

        mat1_np = TestHelper.gen_fill_matrix_np(nrow, ncol)
        mat2_np = TestHelper.gen_fill_matrix_np(nrow, ncol)
        ret_np = np.matmul(mat1_np, mat2_np)

        assert TestHelper.closely_eq(ret, ret_np)

    def test_multiply_mkl(self) -> None:
        nrow, ncol = 512, 512

        mat1 = Matrix(nrow, ncol)
        mat2 = Matrix(nrow, ncol)
        TestHelper.fill_matrix(mat1)
        TestHelper.fill_matrix(mat2)
        ret = multiply_mkl(mat1, mat2)

        mat1_np = TestHelper.gen_fill_matrix_np(nrow, ncol)
        mat2_np = TestHelper.gen_fill_matrix_np(nrow, ncol)
        ret_np = np.matmul(mat1_np, mat2_np)

        assert TestHelper.closely_eq(ret, ret_np)
