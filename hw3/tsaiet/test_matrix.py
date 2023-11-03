import _matrix
import pytest
import numpy as np

def generate_matrix():
	size = 1000
	mat1 = _matrix.Matrix(size, size, np.random.rand(1, size*size).flatten())
	mat2 = _matrix.Matrix(size, size, np.random.rand(1, size*size).flatten())
	return mat1, mat2

def test_multiply():
    mat1, mat2 = generate_matrix
    
    naive = _matrix.multiply_naive(mat1, mat2)
	tile = _matrix.multiply_tile(mat1, mat2, 16)
	mkl = _matrix.multiply_mkl(mat1, mat2)

	assert naive == tile
	assert naive == mkl
	
