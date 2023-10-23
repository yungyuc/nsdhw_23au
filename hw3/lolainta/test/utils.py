from _matrix import Matrix
from random import randint


def generate_matrix(row: int, col: int) -> Matrix:
    m = Matrix(row, col)
    for i in range(row):
        for j in range(col):
            m[i, j] = randint(1, 100)
    return m, row, col
