import matrix
import pytest
import timeit

class Test_Matrix():

    def matrices(self, size):
        mat1 = matrix.Matrix(size, size)
        mat2 = matrix.Matrix(size, size)
        mat3 = matrix.Matrix(size, size)

        for i in range(size):
            for j in range(size):
                mat1[i, j] = i * size + j + 1
                mat2[i, j] = i * size + j + 1
                mat3[i, j] = 0

        return mat1, mat2, mat3

    def test_basic(self):
        size = 100
        mat1, mat2, mat3 = self.matrices(size)

        assert size == mat1.nrow
        assert size == mat1.ncol
        assert size == mat2.nrow
        assert size == mat2.ncol
        assert size == mat3.nrow
        assert size == mat3.ncol

        assert 2 == mat1[0, 1]
        assert size + 2 == mat1[1, 1]
        assert size * 2 == mat1[1, size - 1]
        assert size * size == mat1[size - 1, size - 1]

        for i in range(mat1.nrow):
            for j in range(mat1.ncol):
                assert mat1[i, j] != 0
                assert mat1[i, j] == mat2[i, j]
                assert mat3[i, j] == 0

        assert mat1 == mat2
        assert mat1 is not mat2

    def test_multiply_zero(self):
        dim = 100
        m1, _, m_zero = self.matrices(dim) 

        result_naive = matrix.multiply_naive(m1, m_zero)
        result_mkl = matrix.multiply_mkl(m1, m_zero)

        for i in range(dim):
            for j in range(dim):
                assert result_naive[i, j] == 0
                assert result_mkl[i, j] == 0

    def test_tiling_efficiency(self):
        matrix_size = 1000
        m1, m2, _ = self.matrices(matrix_size)  

        base_tile_size = 0
        ratio_base, time_base = self.tiling_test(m1, m2, base_tile_size)

        for tile_size in [16, 32, 64]:
            ratio, time_tiled = self.tiling_test(m1, m2, tile_size)
            assert ratio < 0.8 * ratio_base, f"Tiling with size {tile_size} should be at least 20% faster."

    @staticmethod
    def tiling_test(mat1, mat2, tile_size):
        def timed_execution(code, globals):
            return min(timeit.Timer(code, globals=globals).repeat(10, 1))

        globals_for_testing = dict(matrix=matrix, mat1=mat1, mat2=mat2, tile_size=tile_size)
        tile_code = f"matrix.multiply_tile(mat1, mat2, tile_size)" if tile_size else "matrix.multiply_naive(mat1, mat2)"

        time_tiled = timed_execution(tile_code, globals_for_testing)
        time_mkl = timed_execution('matrix.multiply_mkl(mat1, mat2)', globals_for_testing)

        performance_ratio = time_tiled / time_mkl

        return performance_ratio, time_tiled
