from _matrix import Matrix
from random import randint
from utils import generate_matrix


def test_construct():
    row = randint(1, 100)
    col = randint(1, 100)
    m = Matrix(row, col)
    assert m.nrow == row
    assert m.ncol == col

    m, r, c = generate_matrix(randint(1, 100), randint(1, 100))
    assert m.nrow == r
    assert m.ncol == c


def test_empty_matrix():
    try:
        Matrix(0, 0)
    except:
        assert False
    else:
        assert True


def test_large_matrix():
    try:
        Matrix(1024, 1024)
    except:
        assert False
    else:
        assert True


def test_zero_initialized():
    row = randint(1, 100)
    col = randint(1, 100)
    m = Matrix(row, col)
    for i in range(row):
        for j in range(col):
            assert m[i, j] == 0


def test_basic():
    size = 100
    mat1 = Matrix(size, size)
    mat2 = Matrix(size, size)
    mat3 = Matrix(size, size)

    for it in range(size):
        for jt in range(size):
            mat1[it, jt] = it * size + jt + 1
            mat2[it, jt] = it * size + jt + 1
            mat3[it, jt] = 0

    assert size == mat1.nrow
    assert size == mat1.ncol
    assert size == mat2.nrow
    assert size == mat2.ncol
    assert size == mat3.nrow
    assert size == mat3.ncol

    assert 2 == mat1[0, 1]
    assert size + 2 == mat1[1, 1]
    assert size * 2 == mat1[1, size - 1]
    assert size * size == mat1[size - 1, size - 1]

    for i in range(mat1.nrow):
        for j in range(mat1.ncol):
            assert 0 != mat1[i, j]
            assert mat1[i, j] == mat2[i, j]
            assert 0 == mat3[i, j]

    assert mat1 == mat2
    assert mat1 is not mat2
