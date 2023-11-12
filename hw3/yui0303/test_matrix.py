import _matrix
from time import process_time

def test_constructor():
    mat1 = _matrix.Matrix(2, 2)
    mat4 = _matrix.Matrix(1000, 1000)
    assert(mat1.nrow == mat1.ncol == 2)
    assert(mat4.nrow == mat4.ncol == 1000)
    arr = [1, 0, 0, 1]
    mat3 = _matrix.Matrix(2, 2, arr)
    for i in range(mat3.nrow):
        for j in range(mat3.ncol):
            assert(arr[i*mat3.nrow+j] == mat3[i, j])

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

def test_mul():
    mat1 = _matrix.Matrix(3, 3, [1, 0, 0, 0, 1, 0, 0, 0, 1])
    mat2 = _matrix.Matrix(3, 3, [x+1 for x in range(9)])
    ans = _matrix.Matrix(3, 3, [x+1 for x in range(9)])

    ret_navie = _matrix.multiply_naive(mat1, mat2)
    ret_tile = _matrix.multiply_tile(mat1, mat2, 1)
    ret_mkl = _matrix.multiply_mkl(mat1, mat2)

    assert(ans == ret_navie)
    assert(ans == ret_tile)
    assert(ans ==ret_mkl)

def create_matrices(size):
    m1 = _matrix.Matrix(size, size, [x+1 for x in range(size*size)])
    m2 = _matrix.Matrix(size, size, [1]*(size*size))
    
    return m1, m2

def Timing():
    size = 1024
    repeat = 5
    m1, m2 = create_matrices(size)
    naive_total_time = 0.
    for r in range(repeat):
        naive_start_time = process_time()
        res_naive = _matrix.multiply_naive(m1, m2)
        naive_end_time = process_time()
        naive_total_time += naive_end_time - naive_start_time
        print("[ %d / %d ] Naive approach took: \t%s seconds"%(r+1, repeat, naive_end_time - naive_start_time))
    print("Naive approach average took: \t%s seconds"%(naive_total_time/repeat))
    
    tile_total_time = 0.
    for r in range(repeat):
        tile_start_time = process_time()
        res_tile = _matrix.multiply_tile(m1, m2, 16)
        tile_end_time = process_time()
        tile_total_time += tile_end_time - tile_start_time
        print("[ %d / %d ] Tiling approach took: \t%s seconds"%(r+1, repeat, tile_end_time - tile_start_time))
    print("Tiling approach average took: \t%s seconds"%(tile_total_time/repeat))

    assert(res_naive == res_tile)

    Speedup = naive_total_time/tile_total_time
    print("The Speedup is %.3f"%(Speedup))

    assert(Speedup >= 1.2)

# a funciton to meausure the time each multiplication using different method in Matrix datatype

if __name__ == '__main__':
    # test_constructor()
    # test_zero()
    # test_mul()
    Timing()
