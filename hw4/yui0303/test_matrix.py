import _matrix
import numpy as np
from time import process_time

def test_constructor():
    mat1 = _matrix.Matrix(2, 2)
    mat4 = _matrix.Matrix(1000, 1000)
    assert(mat1.nrow == mat1.ncol == 2)
    assert(mat4.nrow == mat4.ncol == 1000)
    mat2 = _matrix.Matrix(mat1)
    assert(mat1 == mat2)

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

def assert_np_matrix_equal(np_mat, custom_mat):
    for i in range(custom_mat.nrow):
        for j in range(custom_mat.ncol):
            assert(np_mat[i, j] == custom_mat[i, j])

def test_mul():
    # random np matrix int type
    np_mat1 = np.random.randint(0, 100, size=(3, 3))
    np_mat2 = np.random.randint(0, 100, size=(3, 3))
    mat1 = _matrix.Matrix(3, 3)
    mat2 = _matrix.Matrix(3, 3)
    for i in range(3):
        for j in range(3):
            mat1[i, j] = np_mat1[i, j]
            mat2[i, j] = np_mat2[i, j]
    ans = np.matmul(np_mat1, np_mat2)

    ret_navie = _matrix.multiply_naive(mat1, mat2)
    ret_tile = _matrix.multiply_tile(mat1, mat2, 1)
    ret_mkl = _matrix.multiply_mkl(mat1, mat2)

    assert_np_matrix_equal(ans, ret_navie)
    assert_np_matrix_equal(ans, ret_tile)
    assert_np_matrix_equal(ans, ret_mkl)

def create_matrices(size):
    np_mat1 = np.random.randint(0, 100, size=(size, size))
    np_mat2 = np.random.randint(0, 100, size=(size, size))
    mat1 = _matrix.Matrix(size, size)
    mat2 = _matrix.Matrix(size, size)
    for i in range(size):
        for j in range(size):
            mat1[i, j] = np_mat1[i, j]
            mat2[i, j] = np_mat2[i, j]
    
    return mat1, mat2

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