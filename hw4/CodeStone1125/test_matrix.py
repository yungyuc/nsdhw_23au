import pytest
import _matrix
import random
import numpy as np
import timeit
import math
import sys
import os
import pytest
from pytest import approx as ap  # import approx
import timeit
import _matrix
import unittest


# def test_matrix_creation():
#     rows = random.randint(1, 1000)
#     cols = random.randint(1, 1000)
#     mat = _matrix.Matrix(rows, cols)
#     assert mat.nrow == rows
#     assert mat.ncol == cols

# def test_matrix_get_set_value():
#     rows = random.randint(1, 1000)
#     cols = random.randint(1, 1000)
#     mat = _matrix.Matrix(rows, cols)
    
#     # Generate random row and column indices
#     row_index = random.randint(0, rows - 1)
#     col_index = random.randint(0, cols - 1)
    
#     # Generate a random value
#     random_value = random.uniform(100.0, 10000.0)
    
#     mat.setvalue(row_index, col_index, random_value)
#     assert mat.getvalue(row_index, col_index) == random_value

# def test_matrix_buffer_vector():
#     rows = 2
#     cols = 3
#     # Generate random data for the matrix
#     mat_data = [random.uniform(100.0, 10000.0) for _ in range(rows * cols)]
#     mat = _matrix.Matrix(rows, cols, mat_data)

#     # Get the buffer vector
#     buffer = mat.buffer_vector()

#     # Check if each element in the buffer is equal to its corresponding element in the data
#     for i in range(rows * cols):
#         assert buffer[i] == mat_data[i]

# def test_matrix_getitem_setitem():
#     rows, cols = 100, 1000
#     mat = _matrix.Matrix(rows, cols)
    
#     # Set a random value at a random position
#     random_row = random.randint(0, rows - 1)
#     random_col = random.randint(0, cols - 1)
#     random_value = random.uniform(100.0, 10000.0)
    
#     mat[(random_row, random_col)] = random_value
    
#     # Verify that the value was set correctly
#     assert mat[(random_row, random_col)] == random_value

# def test_matrix_multiplication():
#     tolerance = 1e-6 
#     # Generate random data for mat1 and mat2
#     mat1_data = np.random.rand(100, 100).flatten().tolist()
#     mat2_data = np.random.rand(100, 100).flatten().tolist()

#     mat1 = _matrix.Matrix(100, 100, mat1_data)
#     mat2 = _matrix.Matrix(100, 100, mat2_data)
    
#     result = _matrix.multiply_naive(mat1, mat2)
    
#     # Calculate the expected result using numpy
#     expected_result = np.dot(np.array(mat1_data).reshape(100, 100), np.array(mat2_data).reshape(100, 100))
    
#     # Check each element of the result matrix
#     for i in range(100):
#         for j in range(100):
#             assert math.isclose(result[(i, j)], expected_result[i][j], rel_tol=tolerance)

# if __name__ == "__main__":
#     pytest.main()
class GradingTest(unittest.TestCase):

    def make_matrices(self, size):

        mat1 = _matrix.Matrix(size,size)
        mat2 = _matrix.Matrix(size,size)
        mat3 = _matrix.Matrix(size,size)

        for it in range(size):
            for jt in range(size):
                mat1[it, jt] = it * size + jt + 1
                mat2[it, jt] = it * size + jt + 1
                mat3[it, jt] = 0

        return mat1, mat2, mat3

    def test_basic(self):

        self.assertEqual(0, _matrix.bytes())

        size = 100
        mat1, mat2, mat3, *_ = self.make_matrices(size)
        self.assertEqual(3*8 * size*size, _matrix.bytes())
        base_alloc = _matrix.allocated()
        base_dealloc = _matrix.deallocated()

        self.assertEqual(size, mat1.nrow)
        self.assertEqual(size, mat1.ncol)
        self.assertEqual(size, mat2.nrow)
        self.assertEqual(size, mat2.ncol)
        self.assertEqual(size, mat3.nrow)
        self.assertEqual(size, mat3.ncol)

        self.assertEqual(2, mat1[0,1])
        self.assertEqual(size+2, mat1[1,1])
        self.assertEqual(size*2, mat1[1,size-1])
        self.assertEqual(size*size, mat1[size-1,size-1])

        for i in range(mat1.nrow):
            for j in range(mat1.ncol):
                self.assertNotEqual(0, mat1[i,j])
                self.assertEqual(mat1[i,j], mat2[i,j])
                self.assertEqual(0, mat3[i,j])

        self.assertEqual(mat1, mat2)
        self.assertTrue(mat1 is not mat2)

        self.assertEqual(3*8 * size*size, _matrix.bytes())
        self.assertEqual(base_alloc, _matrix.allocated())
        self.assertEqual(base_dealloc, _matrix.deallocated())

    def test_match_naive_mkl(self):

        self.assertEqual(0, _matrix.bytes())

        size = 100
        mat1, mat2, *_ = self.make_matrices(size)
        self.assertEqual(3*8 * size*size, _matrix.bytes())
        base_alloc = _matrix.allocated()
        base_dealloc = _matrix.deallocated()

        ret_naive = _matrix.multiply_naive(mat1, mat2)
        ret_mkl = _matrix.multiply_mkl(mat1, mat2)

        self.assertEqual(size, ret_naive.nrow)
        self.assertEqual(size, ret_naive.ncol)
        self.assertEqual(size, ret_mkl.nrow)
        self.assertEqual(size, ret_mkl.ncol)

        for i in range(ret_naive.nrow):
            for j in range(ret_naive.ncol):
                self.assertNotEqual(mat1[i,j], ret_mkl[i,j])
                self.assertEqual(ret_naive[i,j], ret_mkl[i,j])

        self.assertEqual(5*8 * size*size, _matrix.bytes())
        self.assertEqual(base_alloc + 2*8 * size*size, _matrix.allocated())
        self.assertEqual(base_dealloc, _matrix.deallocated())

    def test_zero(self):

        self.assertEqual(0, _matrix.bytes())

        size = 200
        mat1, mat2, mat3, *_ = self.make_matrices(size)
        self.assertEqual(3*8 * size*size, _matrix.bytes())
        base_alloc = _matrix.allocated()
        base_dealloc = _matrix.deallocated()

        ret_naive = _matrix.multiply_naive(mat1, mat3)
        ret_mkl = _matrix.multiply_mkl(mat1, mat3)

        self.assertEqual(size, ret_naive.nrow)
        self.assertEqual(size, ret_naive.ncol)
        self.assertEqual(size, ret_mkl.nrow)
        self.assertEqual(size, ret_mkl.ncol)

        for i in range(ret_naive.nrow):
            for j in range(ret_naive.ncol):
                self.assertEqual(0, ret_naive[i,j])
                self.assertEqual(0, ret_mkl[i,j])

        self.assertEqual(5*8 * size*size, _matrix.bytes())
        self.assertEqual(base_alloc + 2*8 * size*size, _matrix.allocated())
        self.assertEqual(base_dealloc, _matrix.deallocated())

    def test_memory(self):

        self.assertEqual(0, _matrix.bytes())
        base_alloc = _matrix.allocated()
        base_dealloc = _matrix.deallocated()

        size = 100
        mat1, mat2, mat3, *_ = self.make_matrices(size)
        self.assertEqual(3*8 * size*size, _matrix.bytes())
        # New allocation.
        self.assertEqual(base_alloc + 3*8 * size*size, _matrix.allocated())
        # No deallocation.
        self.assertEqual(base_dealloc, _matrix.deallocated())
        mat1 = mat2 = mat3 = None
        # Matrices are deallocated.
        self.assertEqual(0, _matrix.bytes())
        self.assertEqual(base_dealloc + 3*8 * size*size, _matrix.deallocated())
        self.assertEqual(base_alloc + 3*8 * size*size, _matrix.allocated())


if __name__ == "__main__":
    unittest.main()
