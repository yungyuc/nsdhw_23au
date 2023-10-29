import pytest
import random


from _matrix import Matrix, multiply_naive, multiply_mkl, multiply_tile


def test_matrix_size():
    rows = random.randint(1, 10)
    cols = random.randint(1, 10)
    mat = Matrix(rows, cols)
    assert mat.nrow == rows
    assert mat.ncol == cols

def test_equal():

    mat1 = Matrix(2, 2)
    mat1[1, 0] = 12
    mat1[0, 1] = 30
    
    mat2 = Matrix(2, 2)
    mat2[1, 0] = 12
    mat2[0, 1] = 30

    #print(mat1)
    #print(mat1 == mat2)
    
    assert mat1 == mat2


def test_set_and_get():

    mat = Matrix(2, 2)
    mat[1, 0] = 12
    mat[0, 1] = 30

    assert mat[1, 0] == 12
    assert mat[0, 1] == 30





def test_multiply():

    mat1 = Matrix(2, 2)
    mat1[1, 0] = 12
    mat1[0, 1] = 30
    mat1[0, 0] = 40


    mat2 = Matrix(2, 2)
    mat2[1, 0] = 11
    mat2[0, 1] = 30


    ret1 = multiply_mkl(mat1, mat2)
    ret2 = multiply_naive(mat1, mat2)
    ret3 = multiply_tile(mat1, mat2, 16)


    assert ret1 == ret2
    assert ret3 == ret1



if __name__ == '__main__':
    pytest.main()