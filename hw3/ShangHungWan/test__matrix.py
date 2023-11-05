import pytest
import unittest
import _matrix


class MatrixTest(unittest.TestCase):
    def new_matrix(self, size: int):
        matrix = _matrix.Matrix(size, size)
        for it in range(size):
            for jt in range(size):
                matrix[it, jt] = it * size + jt + 1

        return matrix

    def test_uat(self):
        size = 100
        mat1 = self.new_matrix(size)
        mat2 = self.new_matrix(size)

        result = _matrix.multiply_naive(mat1, mat2)
        tile_result = _matrix.multiply_tile(mat1, mat2, 10)
        mkl_result = _matrix.multiply_mkl(mat1, mat2)

        for i in range(result.nrow):
            for j in range(result.ncol):
                self.assertNotEqual(mat1[i, j], result[i, j])
                self.assertNotEqual(mat1[i, j], tile_result[i, j])
                self.assertNotEqual(mat1[i, j], mkl_result[i, j])

                self.assertEqual(
                    result[i, j],
                    tile_result[i, j],
                    (i, j, result[i, j], tile_result[i, j], mkl_result[i, j]),
                )
                self.assertEqual(result[i, j], mkl_result[i, j])

        self.assertEqual(result, tile_result)
        self.assertEqual(result, mkl_result)

    def test_not_equal(self):
        size = 100
        mat1 = self.new_matrix(size)
        mat2 = _matrix.Matrix(size, size)

        for it in range(size):
            for jt in range(size):
                mat2[it, jt] = it + jt * size + 1

        self.assertNotEqual(mat1, mat2)

    def test_nrow(self):
        mat2 = _matrix.Matrix(1, 2)
        self.assertEqual(mat2.nrow, 1)

    def test_ncol(self):
        mat2 = _matrix.Matrix(1, 2)
        self.assertEqual(mat2.ncol, 2)

    def test_getitem_and_setitem(self):
        mat2 = _matrix.Matrix(1, 2)
        mat2[0, 0] = 1
        mat2[0, 1] = 2

        self.assertEqual(mat2[0, 0], 1)
        self.assertEqual(mat2[0, 1], 2)

    def test_not_equal_type(self):
        mat1 = self.new_matrix(2)
        mat2 = self.new_matrix(3)

        with pytest.raises(IndexError):
            _matrix.multiply_naive(mat1, mat2)

        with pytest.raises(IndexError):
            _matrix.multiply_tile(mat1, mat2, 16)

        with pytest.raises(IndexError):
            _matrix.multiply_mkl(mat1, mat2)

    def test_aliquant_tile(self):
        size = 100
        mat1 = self.new_matrix(size)
        mat2 = self.new_matrix(size)

        result = _matrix.multiply_tile(mat1, mat2, 16)

        for it in range(size):
            for jt in range(size):
                self.assertNotEqual(mat1[it, jt], result[it, jt])
                self.assertNotEqual(0, result[it, jt])
