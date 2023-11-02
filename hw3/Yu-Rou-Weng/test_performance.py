import matrix
import pytest
import timeit

class Test_Matrix():
    @staticmethod
    def matrices(dimension):
        matrix_a = matrix.Matrix(dimension, dimension)
        matrix_b = matrix.Matrix(dimension, dimension)

        for i in range(dimension):
            for j in range(dimension):
                matrix_a[i, j] = i * dimension + j + 1
                matrix_b[i, j] = i * dimension + j + 1

        return matrix_a, matrix_b

    def test_multiply_correct(self):
        dim = 100
        m1, m2 = self.matrices(dim)

        result_naive = matrix.multiply_naive(m1, m2)
        result_mkl = matrix.multiply_mkl(m1, m2)

        for i in range(dim):
            for j in range(dim):
                assert result_naive[i, j] == result_mkl[i, j]

    def test_multiply_zero(self):
        dim = 100
        m1, m2 = self.matrices(dim)
        m_zero = matrix.Matrix(dim, dim)  
        for i in range(dim):
            for j in range(dim):
                m_zero[i, j] = 0

        result_naive = matrix.multiply_naive(m1, m_zero)
        result_mkl = matrix.multiply_mkl(m1, m_zero)

        for i in range(dim):
            for j in range(dim):
                assert result_naive[i, j] == 0
                assert result_mkl[i, j] == 0

    def test_tiling_efficiency(self):
        matrix_size = 1000
        m1, m2 = self.matrices(matrix_size)
        base_tile_size = 0 
        ratio_base, time_base = self.tiling_test(m1, m2, base_tile_size)

        for tile_size in [16, 17, 19]:
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
