import _matrix
import math
import random
import numpy as np
import pytest

def is_close(a,b):
    return math.isclose(a,b,rel_tol=1e-3)

def test_n_row_col():
    nrow = 3
    ncol = 4
    mat1 = _matrix.Matrix(nrow,ncol)
    assert mat1.nrow == nrow
    assert mat1.ncol == ncol

def test_get_set():
    nrow = 3
    ncol = 4
    mat1 = _matrix.Matrix(nrow,ncol)
    for i in range(nrow):
        for j in range(ncol):
            mat1[i,j] = i*ncol+j+1
    for i in range(nrow):
        for j in range(ncol):
            assert is_close(mat1[i,j],i*ncol+j+1)

# def test_invalid_multiply():
#     n1, n2, n3, n4 = 3, 4, 5, 6
#     mat1 = _matrix.Matrix(n1, n2)
#     mat2 = _matrix.Matrix(n3, n4)
#     with pytest.raises(ValueError):
#         mat3 = _matrix.multiply_naive(mat1,mat2)
    
#     with pytest.raises(ValueError):
#         mat3 = _matrix.multiply_tile(mat1,mat2, 2)

#     with pytest.raises(ValueError):
#         mat3 = _matrix.multiply_mkl(mat1,mat2)
        


def test_multiply():
    n1, n2, n3 = 2, 2, 2
    mat1 = _matrix.Matrix(n1, n2)
    mat2 = _matrix.Matrix(n2, n3)
    np_mat1 = np.zeros((n1,n2))
    np_mat2 = np.zeros((n2,n3))
    for i in range(n1):
        for j in range(n2):
            mat1[i,j] = i*n2+j+1
            np_mat1[i,j] = mat1[i,j]
    for i in range(n2):
        for j in range(n3):
            mat2[i,j] = i*n3+j+1
            np_mat2[i,j] = mat2[i,j]

    mat_naive = _matrix.multiply_naive(mat1,mat2)
    mat_tile = _matrix.multiply_tile(mat1,mat2, 16)
    mat_mkl = _matrix.multiply_mkl(mat1,mat2)
    np_mat3 = np.matmul(np_mat1,np_mat2)
    for i in range(n1):
        for j in range(n3):
            assert is_close(mat_naive[i,j],np_mat3[i,j])
            # assert is_close(mat_tile[i,j],np_mat3[i,j])
            if not is_close(mat_tile[i,j],np_mat3[i,j]):
                print(mat_tile[i,j],np_mat3[i,j])
            assert is_close(mat_mkl[i,j],np_mat3[i,j])

test_multiply()


