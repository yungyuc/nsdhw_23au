from utils import generate_matrix
from _matrix import multiply_naive, multiply_mkl, Matrix


def test_zero():
    mat1 = Matrix(100, 100)
    mat2 = Matrix(100, 100)
    res1 = multiply_naive(mat1, mat2)
    res2 = multiply_mkl(mat1, mat2)
    assert res1.nrow == 100
    assert res1.ncol == 100
    assert res2.nrow == 100
    assert res2.ncol == 100
    for i in range(res1.nrow):
        for j in range(res1.ncol):
            assert res1[i, j] == 0
            assert res2[i, j] == 0


def test_equal():
    mat1, r1, c1 = generate_matrix(100, 100)
    mat2, r2, c2 = generate_matrix(100, 100)
    res1 = multiply_naive(mat1, mat2)
    res2 = multiply_mkl(mat1, mat2)
    assert res1.nrow == r1
    assert res1.ncol == c2
    assert res2.nrow == r1
    assert res2.ncol == c2
    for i in range(res1.nrow):
        for j in range(res1.ncol):
            assert res1[i, j] == res2[i, j]
