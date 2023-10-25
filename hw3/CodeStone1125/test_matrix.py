#!/usr/bin/python3

import _matrix
import pytest
import numpy as np
import math
import time

def is_mat_equal(mat1, mat2, eps=1e-6):
    if mat1.ncol != mat2.ncol or mat1.nrow != mat2.nrow:
        return False

    for i in range(mat1.nrow):
        for j in range(mat1.ncol):
            if not math.isclose(mat1[i,j], mat2[i,j], abs_tol=eps):
                return False

    return True


def np_random_mat(nrow, ncol):
    return np.random.rand(nrow, ncol) * 1000.0

def np_to_matrix(npmat):
    mat = _matrix.Matrix(npmat.shape[0], npmat.shape[1])

    for i in range(npmat.shape[0]):
        for j in range(npmat.shape[1]):
            mat[i,j] = npmat[i][j]

    return mat

def test_mul_naive():
    for _ in range(200):
        npm1 = np_random_mat(50, 50)
        npm2 = np_random_mat(50, 50)
        m1 = np_to_matrix(npm1)
        m2 = np_to_matrix(npm2)
        m3 = _matrix.multiply_naive(m1, m2)
        mref = np_to_matrix(np.matmul(npm1, npm2))
        assert is_mat_equal(m3, mref)

def test_mul_tile():
    for _ in range(200):
        npm1 = np_random_mat(50, 50)
        npm2 = np_random_mat(50, 50)
        m1 = np_to_matrix(npm1)
        m2 = np_to_matrix(npm2)
        m3 = _matrix.multiply_tile(m1, m2, 16)
        mref = np_to_matrix(np.matmul(npm1, npm2))
        assert is_mat_equal(m3, mref)

def test_mul_mkl():
    for _ in range(200):
        npm1 = np_random_mat(50, 50)
        npm2 = np_random_mat(50, 50)
        m1 = np_to_matrix(npm1)
        m2 = np_to_matrix(npm2)
        m3 = _matrix.multiply_mkl(m1, m2)
        mref = np_to_matrix(np.matmul(npm1, npm2))
        assert is_mat_equal(m3, mref)

def test_performance():
    npm1 = np_random_mat(1200, 1200)
    npm2 = np_random_mat(1200, 1200)
    m1 = np_to_matrix(npm1)
    m2 = np_to_matrix(npm2)

    tStart = time.process_time()
    m_naive = _matrix.multiply_naive(m1, m2)
    tNaive = time.process_time() - tStart

    tStart = time.process_time()
    m_tile16 = _matrix.multiply_tile(m1, m2, 16)
    tTile16 = time.process_time() - tStart

    tStart = time.process_time()
    m_tile64 = _matrix.multiply_tile(m1, m2, 64)
    tTile64 = time.process_time() - tStart

    tStart = time.process_time()
    m_tile256 = _matrix.multiply_tile(m1, m2, 256)
    tTile256 = time.process_time() - tStart

    tStart = time.process_time()
    m_mkl = _matrix.multiply_mkl(m1, m2)
    tMKL = time.process_time() - tStart

    m_ref = np_to_matrix(np.matmul(npm1, npm2))

    assert is_mat_equal(m_ref, m_naive)
    assert is_mat_equal(m_ref, m_tile16)
    assert is_mat_equal(m_ref, m_tile64)
    assert is_mat_equal(m_ref, m_tile256)
    assert is_mat_equal(m_ref, m_mkl)
    assert tTile16  < 0.8 * tNaive
    assert tTile64  < 0.8 * tNaive
    assert tTile256 < 0.8 * tNaive

    with open("performance.txt", "w") as fh:
        fh.write(f'Multiplication in naive way: {tNaive: 10.4f} sec.\n')
        fh.write(f'-----------------------------------------------------------------------\n')
        fh.write(f'Multiplication use tiling: {tTile16: 10.4f} sec.\n')
        faster = (tNaive / tTile16)
        fh.write(f'Multiplication use tiling(16) faster than in naive way: {faster: 10.4f} times.\n')
        fh.write(f'-----------------------------------------------------------------------\n')
        fh.write(f'Multiplication use tiling: {tTile64: 10.4f} sec.\n')
        faster = (tNaive / tTile64)
        fh.write(f'Multiplication use tiling(64) faster than in naive way: {faster: 10.4f} times.\n')
        fh.write(f'-----------------------------------------------------------------------\n')
        fh.write(f'Multiplication use tiling: {tTile256: 10.4f} sec.\n')
        faster = (tNaive / tTile256)
        fh.write(f'Multiplication use tiling(256) faster than in naive way: {faster: 10.4f} times.\n')
        fh.write(f'-----------------------------------------------------------------------\n')
        fh.write(f'Multiplication by MKL: {tMKL: 10.4f} sec.\n')
        faster = (tNaive / tMKL)
        fh.write(f'Multiplication use MKL faster than in naive way: {faster: 10.4f} times.\n')