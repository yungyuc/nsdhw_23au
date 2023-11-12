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
    naive = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', setup=setup)
    mkl = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', setup=setup)
    tile = timeit.Timer('_matrix.multiply_tile(mat1, mat2, 16)', setup=setup)

    repeat = 5

    naive_time = naive.repeat(repeat=repeat, number=1)
    mkl_time = mkl.repeat(repeat=repeat, number=1)
    tile_time = tile.repeat(repeat=repeat, number=1)

    with open('performance.txt', 'w') as f:
        f.write('naive:\n')
        f.write('min: ' + str(min(naive_time)) + '\n')
        f.write('max: ' + str(max(naive_time)) + '\n')
        f.write('mean: ' + str(sum(naive_time)/len(naive_time)) + '\n')

        f.write('mkl:\n')
        f.write('min: ' + str(min(mkl_time)) + '\n')
        f.write('max: ' + str(max(mkl_time)) + '\n')
        f.write('mean: ' + str(sum(mkl_time)/len(mkl_time)) + '\n')

        f.write('tile:\n')
        f.write('min: ' + str(min(tile_time)) + '\n')
        f.write('max: ' + str(max(tile_time)) + '\n')
        f.write('mean: ' + str(sum(tile_time)/len(tile_time)) + '\n')

        f.write('tile/naive:\n')
        f.write( str(min(tile_time)/min(naive_time)) + '\n')

        f.write('mkl/naive:\n')
        f.write( str(min(mkl_time)/min(naive_time)) + '\n')


if __name__ == '__main__':
    benchmark()