import sys
import os
import timeit
import unittest

# The python module that wraps the matrix code.
import _matrix


def test_zero():
    mat1 = _matrix.Matrix(2, 2)
    mat1[0, 0] = 0
    mat1[0, 1] = 0
    mat1[1, 0] = 0
    mat1[1, 1] = 0
    mat2 = _matrix.Matrix(2, 2)
    mat2[0, 0] = 1
    mat2[0, 1] = 2
    mat2[1, 0] = 3
    mat2[1, 1] = 4

    ret_navie = _matrix.multiply_naive(mat1, mat2)
    ret_tile = _matrix.multiply_tile(mat1, mat2, 1)
    ret_mkl = _matrix.multiply_mkl(mat1, mat2)

    assert (ret_navie == ret_tile)
    assert (ret_navie == ret_mkl)

    for i in range(2):
        for j in range(2):
            assert mat1[i, j] == ret_navie[i, j]


def test_identity():
    mat1 = _matrix.Matrix(2, 2)
    mat1[0, 0] = 1
    mat1[1, 1] = 1
    mat2 = _matrix.Matrix(2, 2)
    mat2[0, 0] = 1
    mat2[0, 1] = 2
    mat2[1, 0] = 3
    mat2[1, 1] = 4

    ret_naive = _matrix.multiply_naive(mat1, mat2)
    ret_tile = _matrix.multiply_tile(mat1, mat2, 1)
    ret_mkl = _matrix.multiply_mkl(mat1, mat2)

    assert (ret_naive == ret_tile)
    assert (ret_naive == ret_mkl)

    for i in range(2):
        for j in range(2):
            assert mat2[i, j] == ret_naive[i, j]


def test_real():
    mat1 = _matrix.Matrix(2, 2)
    mat1[0, 0] = 1
    mat1[0, 1] = 2
    mat1[1, 0] = 3
    mat1[1, 1] = 4
    mat2 = _matrix.Matrix(2, 2)
    mat2[0, 0] = 5
    mat2[0, 1] = 6
    mat2[1, 0] = 7
    mat2[1, 1] = 8

    ret_navie = _matrix.multiply_naive(mat1, mat2)
    ret_tile = _matrix.multiply_tile(mat1, mat2, 1)
    ret_mkl = _matrix.multiply_mkl(mat1, mat2)

    assert (ret_navie == ret_tile)
    assert (ret_navie == ret_mkl)

    assert ret_navie[0, 0] == 19
    assert ret_navie[0, 1] == 22
    assert ret_navie[1, 0] == 43
    assert ret_navie[1, 1] == 50


class GradingTest(unittest.TestCase):

    def make_matrices(self, size):

        mat1 = _matrix.Matrix(size, size)
        mat2 = _matrix.Matrix(size, size)
        mat3 = _matrix.Matrix(size, size)

        for it in range(size):
            for jt in range(size):
                mat1[it, jt] = it * size + jt + 1
                mat2[it, jt] = it * size + jt + 1
                mat3[it, jt] = 0

        return mat1, mat2, mat3

    def test_basic(self):

        size = 100
        mat1, mat2, mat3, *_ = self.make_matrices(size)

        self.assertEqual(size, mat1.nrow)
        self.assertEqual(size, mat1.ncol)
        self.assertEqual(size, mat2.nrow)
        self.assertEqual(size, mat2.ncol)
        self.assertEqual(size, mat3.nrow)
        self.assertEqual(size, mat3.ncol)

        self.assertEqual(2, mat1[0, 1])
        self.assertEqual(size+2, mat1[1, 1])
        self.assertEqual(size*2, mat1[1, size-1])
        self.assertEqual(size*size, mat1[size-1, size-1])

        for i in range(mat1.nrow):
            for j in range(mat1.ncol):
                self.assertNotEqual(0, mat1[i, j])
                self.assertEqual(mat1[i, j], mat2[i, j])
                self.assertEqual(0, mat3[i, j])

        self.assertEqual(mat1, mat2)
        self.assertTrue(mat1 is not mat2)

    def test_match_naive_mkl(self):

        size = 100
        mat1, mat2, *_ = self.make_matrices(size)

        ret_naive = _matrix.multiply_naive(mat1, mat2)
        ret_mkl = _matrix.multiply_mkl(mat1, mat2)

        self.assertEqual(size, ret_naive.nrow)
        self.assertEqual(size, ret_naive.ncol)
        self.assertEqual(size, ret_mkl.nrow)
        self.assertEqual(size, ret_mkl.ncol)

        for i in range(ret_naive.nrow):
            for j in range(ret_naive.ncol):
                self.assertNotEqual(mat1[i, j], ret_mkl[i, j])
                self.assertEqual(ret_naive[i, j], ret_mkl[i, j])

    def test_zero(self):

        size = 100
        mat1, mat2, mat3, *_ = self.make_matrices(size)

        ret_naive = _matrix.multiply_naive(mat1, mat3)
        ret_mkl = _matrix.multiply_mkl(mat1, mat3)

        self.assertEqual(size, ret_naive.nrow)
        self.assertEqual(size, ret_naive.ncol)
        self.assertEqual(size, ret_mkl.nrow)
        self.assertEqual(size, ret_mkl.ncol)

        for i in range(ret_naive.nrow):
            for j in range(ret_naive.ncol):
                self.assertEqual(0, ret_naive[i, j])
                self.assertEqual(0, ret_mkl[i, j])

    def check_tile(self, mat1, mat2, tsize):

        if 0 == tsize:
            ret_tile = _matrix.multiply_naive(mat1, mat2)
            tile_str = "_matrix.multiply_naive(mat1, mat2)"
        else:
            ret_tile = _matrix.multiply_tile(mat1, mat2, tsize)
            tile_str = "_matrix.multiply_tile(mat1, mat2, tsize)"
        ret_mkl = _matrix.multiply_mkl(mat1, mat2)

        for i in range(ret_tile.nrow):
            for j in range(ret_tile.ncol):
                self.assertNotEqual(mat1[i, j], ret_mkl[i, j])
                self.assertEqual(ret_tile[i, j], ret_mkl[i, j])

        ns = dict(_matrix=_matrix, mat1=mat1, mat2=mat2, tsize=tsize)
        t_tile = timeit.Timer(tile_str, globals=ns)
        t_mkl = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', globals=ns)

        time_tile = min(t_tile.repeat(10, 1))
        time_mkl = min(t_mkl.repeat(10, 1))
        ratio = time_tile/time_mkl

        return ratio, time_tile

    def test_tile(self):

        show_ratio = bool(os.environ.get('SHOW_RATIO', False))

        mat1, mat2, *_ = self.make_matrices(500)

        ratio0, time0 = self.check_tile(mat1, mat2, 0)
        if show_ratio:
            print("naive ratio:", ratio0)

        ratio16, time16 = self.check_tile(mat1, mat2, 16)
        if show_ratio:
            print("tile 16 ratio:", ratio16)
            print("time16/time0:", time16/time0)
        self.assertLess(ratio16/ratio0, 0.8)

        ratio17, time17 = self.check_tile(mat1, mat2, 17)
        if show_ratio:
            print("tile 17 ratio:", ratio17)
            print("time17/time0:", time17/time0)
        self.assertLess(ratio17/ratio0, 0.8)

        ratio19, time19 = self.check_tile(mat1, mat2, 19)
        if show_ratio:
            print("tile 19 ratio:", ratio19)
            print("time19/time0:", time19/time0)
        self.assertLess(ratio19/ratio0, 0.8)


class Writer:

    def __init__(self, streams):

        self.streams = streams

    def write(self, msg):

        for stream in self.streams:

            stream.write(msg)


def benchmark():

    setup = '''
import _matrix

size = 1000

mat1 = _matrix.Matrix(size,size)
mat2 = _matrix.Matrix(size,size)

for it in range(size):
    for jt in range(size):
        mat1[it, jt] = it * size + jt + 1
        mat2[it, jt] = it * size + jt + 1
'''

    naive = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', setup=setup)
    tile64 = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 64)', setup=setup)
    mkl = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', setup=setup)

    repeat = 5

    with open('performance.txt', 'w') as fobj:
        w = Writer([sys.stdout, fobj])

        w.write(f'Start multiply_naive (repeat={repeat}), take min = ')
        naivesec = minsec = min(naive.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_tile (repeat={repeat}), take min = ')
        tile64sec = minsec = min(tile64.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_mkl (repeat={repeat}), take min = ')
        mklsec = minsec = min(mkl.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write('\nTiling64 speed-up over naive: %g x\n' % (naivesec/tile64sec))
        w.write('MKL speed-up over naive     : %g x\n' % (naivesec/mklsec))
        w.write('MKL speed-up over tile      : %g x\n' % (tile64sec/mklsec))


if __name__ == '__main__':
    benchmark()
