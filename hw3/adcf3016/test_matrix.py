import pytest
import numpy as np
import random
from _matrix import *

def get_np_matrix(n, m, mat):
    mat_np = np.zeros((n, m))
    for i in range(n):
        for j in range(m):
            mat_np[i, j] = mat[i, j]
    return mat_np

def generate_value(mat):
    for i in range(mat.nrow):
        for j in range(mat.ncol):
            mat[i, j] = i * mat.nrow + j

def test_matrix_constructor():
    row = random.randint(1, 1000)
    col = random.randint(1, 1000)
    mat = Matrix(row, col)
    assert mat.nrow == row
    assert mat.ncol == col

def test_matrix_setter_getter():
    row, col = 1000, 1000
    mat = Matrix(row, col)
    random_row = random.randint(0, row - 1)
    random_col = random.randint(0, col - 1)
    random_value = random.random()
    mat[(random_row, random_col)] = random_value
    assert mat[(random_row, random_col)] == random_value

def test_naive():
    row_size = 1000
    col_size = 1000
    mat1 = Matrix(row_size, col_size)
    mat2 = Matrix(row_size, col_size)
    generate_value(mat1)
    generate_value(mat2)
    A_np = get_np_matrix(row_size, col_size, mat1)
    B_np = get_np_matrix(row_size, col_size, mat2)
    naive_ans = multiply_naive(mat1, mat2)
    naive_ans_np = np.matmul(A_np, B_np)
    for i in range(row_size):
        for j in range(col_size):
            assert abs(naive_ans[i, j] - naive_ans_np[i, j]) < 1e-6

def test_tile():
    tile_size = 16
    row_size = 1000
    col_size = 1000
    mat1 = Matrix(row_size, col_size)
    mat2 = Matrix(row_size, col_size)
    generate_value(mat1)
    generate_value(mat2)
    C_np = get_np_matrix(row_size, col_size, mat1)
    D_np = get_np_matrix(row_size, col_size, mat2)
    tile_ans = multiply_tile(mat1, mat2, tile_size)
    tile_ans_np = np.matmul(C_np, D_np)
    for i in range(row_size):
        for j in range(col_size):
            assert abs(tile_ans[i, j] - tile_ans_np[i, j]) < 1e-6

def test_mkl():
    row_size = 1000
    col_size = 1000
    mat1 = Matrix(row_size, col_size)
    mat2 = Matrix(row_size, col_size)
    generate_value(mat1)
    generate_value(mat2)
    A_np = get_np_matrix(row_size, col_size, mat1)
    B_np = get_np_matrix(row_size, col_size, mat2)
    mkl_ans = multiply_mkl(mat1, mat2)
    mkl_ans_np = np.matmul(A_np, B_np)
    for i in range(row_size):
        for j in range(col_size):
            assert abs(mkl_ans[i, j] - mkl_ans_np[i, j]) < 1e-6
