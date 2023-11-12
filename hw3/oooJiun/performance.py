import _matrix
import timeit

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

    repeat = 5

    naive_time = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', setup=setup)
    tile_time = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 16)', setup=setup)
    mkl_time = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', setup=setup)

    with open('performance.txt', 'w') as f:
        f.write('Start multiply_naive (repeat=5), take min = ')
        naiveTime = min(naive_time.repeat(repeat=repeat, number=1))
        f.write('{} seconds\n'.format(naiveTime))
        print('Start multiply_naive (repeat=5), take min = {} seconds\n'.format(naiveTime))

        f.write('Start multiply_tile (repeat=5), take min = ')
        tileTime = min(tile_time.repeat(repeat=repeat, number=1))
        f.write('{} seconds\n'.format(tileTime))
        print('Start multiply_tile (repeat=5), take min = {} seconds\n'.format(tileTime))
        
        f.write('Start multiply_mkl (repeat=5), take min = ')
        mklTime = min(mkl_time.repeat(repeat=repeat, number=1))
        f.write('{} seconds\n'.format(mklTime))
        print('Start multiply_mkl (repeat=5), take min = {} seconds\n'.format(mklTime))

        f.write('Tile speed-up over naive: {} x\n'.format(tileTime / naiveTime))
        print('Tile speed-up over naive: {} x\n'.format(tileTime / naiveTime))
        f.write('MKL speed-up over naive: {} x\n'.format(mklTime / naiveTime))
        print('MKL speed-up over naive: {} x\n'.format(mklTime / naiveTime))

if __name__ == "__main__":
    benchmark()