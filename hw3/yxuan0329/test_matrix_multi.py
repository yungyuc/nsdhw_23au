import _matrix 
import pytest
import logging

def test_matrix_row_and_col():
    row = 3
    col = 2
    mat = _matrix.Matrix(row, col)

    assert mat.nrow == row
    assert mat.ncol == col

def test_matrix_value():
    mat1 = _matrix.Matrix(1, 3)
    mat1[0, 1] = 1
    mat1[0, 2] = 2
    mat1[0, 0] = 1

    assert mat1[0, 0] == mat1[0, 0]

def test_matrix_equal():
    mat1 = _matrix.Matrix(1, 1)
    mat2 = _matrix.Matrix(1, 1)
    mat3 = _matrix.Matrix(1, 1)
    mat4 = _matrix.Matrix(3, 2)
    mat5 = _matrix.Matrix(3, 2)

    mat1[0, 0] = 1
    mat2[0, 0] = 2
    mat3[0, 0] = 1

    for i in range(3):
        for j in range(2):
            mat4[i, j] = 2.0
            mat5[i, j] = 2.0

    assert mat1 != mat2
    assert mat1 == mat3
    assert mat1 != mat4
    assert mat4 == mat5 

def test_matrix_multi():
    size = 10
    mat1 = _matrix.Matrix(size, size)
    mat2 = _matrix.Matrix(size, size)

    for i in range (size):
        for j in range (size):
            mat1[i, j] = i*i + j + 2.0
            mat2[i, j] = j*j + 2*i + 0.1
    
    new_naive = _matrix.multiply_naive(mat1, mat2)
    new_tile = _matrix.multiply_tile(mat1, mat2, 16)
    new_mkl = _matrix.multiply_mkl(mat1, mat2)

    assert new_naive == new_mkl
    assert new_naive == new_tile
    assert new_tile == new_mkl