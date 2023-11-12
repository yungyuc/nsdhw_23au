import _matrix
import sys
import timeit

class Writer:

    def __init__(self, streams):

        self.streams = streams

    def write(self, msg):

        for stream in self.streams:

            stream.write(msg)

def make_matrices(size):
    mat1 = _matrix.Matrix(size, size)
    mat2 = _matrix.Matrix(size, size)
    mat3 = _matrix.Matrix(size, size)

    for it in range(size):
        for jt in range(size):
            mat1[it, jt] = it * size + jt 
            mat2[it, jt] = it * size + jt
            mat3[it, jt] = 0
    return mat1, mat2, mat3

def benchmark():
    tsize = 16 
    mat1, mat2, mat3 = make_matrices(1000)
    ns = dict(_matrix=_matrix, mat1=mat1, mat2=mat2, tsize=tsize)
    t_naive = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', globals=ns)
    t_tile = timeit.Timer("_matrix.multiply_tile(mat1, mat2, tsize)", globals=ns)
    t_mkl = timeit.Timer("_matrix.multiply_mkl(mat1, mat2)", globals=ns)

    with open('performance.txt', 'w') as fobj:
        repeat = 5

        w = Writer([sys.stdout, fobj])
        w.write('Start multiply_naive using stride=16 (repeat={}), take min = '.format(repeat))
        naivesec = minsec = min(t_naive.repeat(repeat=repeat, number=1))
        w.write('{} seconds\n'.format(minsec))

        w.write('Start multiply_tile (repeat={}), take min = '.format(repeat))
        tilesec = minsec = min(t_tile.repeat(repeat=repeat, number=1))
        w.write('{} seconds\n'.format(minsec))

        w.write('Start multiply_mkl (repeat={}), take min = '.format(repeat))
        mklsec = minsec = min(t_mkl.repeat(repeat=repeat, number=1))
        w.write('{} seconds\n'.format(minsec))


        w.write('Tile speed-up over naive: %g x\n' % (naivesec/tilesec))
        w.write('MKL speed-up over naive: %g x\n' % (naivesec/mklsec))

if __name__ == '__main__':
    benchmark()