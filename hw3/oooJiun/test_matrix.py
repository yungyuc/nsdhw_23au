import pytest
import numpy as np
from _matrix import Matrix, multiply_naive, multiply_tile, generateValue

def get_np_matrix(n, m, mat):
    mat_np = np.zeros((n, m))
    for i in range(n):
        for j in range(m):
            mat_np[i, j] = mat[i, j]
    return mat_np

def test_zero():
    n_size = 100
    m_size = 100
    tile_size = 10
    mat1 = Matrix(n_size, m_size)
    mat2 = Matrix(n_size, m_size)
    generateValue(mat1)
    for i in range(n_size):
        for j in range(m_size):
            mat2[i, j] = 0
    naive_mat = multiply_naive(mat1, mat2)
    tile_mat = multiply_tile(mat1, mat2, tile_size)
    for i in range(n_size):
        for j in range(m_size):
            assert abs(naive_mat[i, j]) < 1e-6
            assert abs(tile_mat[i, j]) < 1e-6

def test_naive():
    n_size = 1000
    m_size = 1000
    mat1 = Matrix(n_size, m_size)
    mat2 = Matrix(n_size, m_size)
    generateValue(mat1)
    generateValue(mat2)
    mat1_np = get_np_matrix(n_size, m_size, mat1)
    mat2_np = get_np_matrix(n_size, m_size, mat2)
    naive_mat = multiply_naive(mat1, mat2)
    naive_np = np.matmul(mat1_np, mat2_np)
    for i in range(n_size):
        for j in range(m_size):
            assert abs(naive_mat[i, j] - naive_np[i, j]) < 1e-6

def test_tile():
    tile_size = 100
    n_size = 1000
    m_size = 1000
    mat1 = Matrix(n_size, m_size)
    mat2 = Matrix(n_size, m_size)
    generateValue(mat1)
    generateValue(mat2)
    mat1_np = get_np_matrix(n_size, m_size, mat1)
    mat2_np = get_np_matrix(n_size, m_size, mat2)
    tile_mat = multiply_tile(mat1, mat2, tile_size)
    tile_np = np.matmul(mat1_np, mat2_np)
    for i in range(n_size):
        for j in range(m_size):
            assert abs(tile_mat[i, j] - tile_np[i, j]) < 1e-6
