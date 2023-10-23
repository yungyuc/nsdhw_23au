from _matrix import Matrix
from random import randint


def generate_matrix(row: int, col: int) -> Matrix:
    m = Matrix(row, col)
    for i in range(row):
        for j in range(col):
            m[i, j] = randint(1, 100)
    return m, row, col


def test_construct():
    row = randint(1, 100)
    col = randint(1, 100)
    m = Matrix(row, col)
    assert m.rows == row
    assert m.cols == col

    m, r, c = generate_matrix(randint(1, 100), randint(1, 100))
    assert m.rows == r
    assert m.cols == c


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
