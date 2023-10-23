from utils import generate_matrix
from _matrix import multiply_naive, multiply_mkl, Matrix


def test_zero():
    mat1 = Matrix(100, 100)
    mat2 = Matrix(100, 100)
    res1 = multiply_naive(mat1, mat2)
    res2 = multiply_mkl(mat1, mat2)
    assert res1.rows == 100
    assert res1.cols == 100
    assert res2.rows == 100
    assert res2.cols == 100
    for i in range(res1.rows):
        for j in range(res1.cols):
            assert res1[i, j] == 0
            assert res2[i, j] == 0


def test_equal():
    mat1, r1, c1 = generate_matrix(100, 100)
    mat2, r2, c2 = generate_matrix(100, 100)
    res1 = multiply_naive(mat1, mat2)
    res2 = multiply_mkl(mat1, mat2)
    assert res1.rows == r1
    assert res1.cols == c2
    assert res2.rows == r1
    assert res2.cols == c2
    for i in range(res1.rows):
        for j in range(res1.cols):
            assert res1[i, j] == res2[i, j]
