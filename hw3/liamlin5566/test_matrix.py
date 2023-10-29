import sys
import pytest
import random
import timeit

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


class Writer:

    def __init__(self, streams):

        self.streams = streams

    def write(self, msg):

        for stream in self.streams:

            stream.write(msg)


def test_performance():
    
    setup = '''
import _matrix
size = 1000
mat1 = _matrix.Matrix(size,size)
mat2 = _matrix.Matrix(size,size)
for it in range(size):
    for jt in range(size):
        mat1[it, jt] = it * size + jt + 1
        mat2[it, jt] = it * size + jt - 1
'''
    
    naive = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', setup=setup)
    tile = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 16)', setup=setup)
    mkl = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', setup=setup)

    repeat = 5

    with open('performance.txt', 'w') as fobj:

        w = Writer([sys.stdout, fobj])

        w.write(f'Start multiply_naive (repeat={repeat}), take min = ')
        naivesec = minsec = min(naive.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_mkl (repeat={repeat}), take min = ')
        mklsec = minsec = min(mkl.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_tile with tsize 16 (repeat={repeat}), take min = ')
        tilesec = minsec = min(tile.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write('Tile 16 speed-up  over naive: %g x\n' % (naivesec/tilesec))
        w.write('MKL speed-up over naive: %g x\n' % (naivesec/mklsec))



if __name__ == '__main__':
    pytest.main()