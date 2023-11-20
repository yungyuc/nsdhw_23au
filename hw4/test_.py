import _matrix
import time
import pytest

def test_correctness():
    size = 1000

    m1 = _matrix.Matrix(size, size)
    m2 = _matrix.Matrix(size, size)

    for it in range(size):
        for jt in range(size):
            m1[it, jt] = it * size + jt + 1
            m2[it, jt] = it * size + jt + 1

    m3_naive = _matrix.multiply_naive(m1, m2)
    m3_tile = _matrix.multiply_tile(m1, m2, 64)
    m3_mkl = _matrix.multiply_mkl(m1, m2)


    assert (m3_naive == m3_tile)
    assert (m3_naive == m3_mkl)

def test_correctness2():
    size = 1000

    m1 = _matrix.Matrix(size, size)
    m2 = _matrix.Matrix(size, size)

    for it in range(size):
        for jt in range(size):
            m1[it, jt] = it * size + jt + 1
            m2[it, jt] = it * size + jt + 1

    time1 = time.time()
    m3_naive = _matrix.multiply_naive(m1, m2)
    time2 = time.time()
    m3_tile = _matrix.multiply_tile(m1, m2, 16)
    time3 = time.time()
    m3_mkl = _matrix.multiply_mkl(m1, m2)
    time4 = time.time()

    # test time
    # with open("performance.txt", "w") as f:
    #     f.write(f"multiply_naive: {time2-time1:.4f} seconds.\n")
    #     f.write(f"multiply_tile: {time3-time2:.4f} seconds.\n")
    #     f.write(f"multiply_mkl: {time4-time3:.4f} seconds.\n")

    assert (m3_naive == m3_tile)
    assert (m3_naive == m3_mkl)