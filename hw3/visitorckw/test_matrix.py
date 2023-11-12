import _matrix

def test_matrix():
    size = 1000
    matrix1 = _matrix.Matrix(size, size)
    matrix2 = _matrix.Matrix(size, size)

    assert(matrix1.nrow == size)
    assert(matrix1.ncol == size)
    assert(matrix2.nrow == size)
    assert(matrix2.ncol == size)

    r = 1

    for i in range(size):
        for j in range(size):
            matrix1[i,j] = r = (r * 725861) % 6599
            matrix2[i,j] = r = (r * 725861) % 6599

    matrix_naive = _matrix.multiply_naive(matrix1, matrix2)
    matrix_tile = _matrix.multiply_tile(matrix1, matrix2, 32)
    matrix_mkl = _matrix.multiply_mkl(matrix1, matrix2)

    for i in range(size):
        for j in range(size):
            assert (matrix_naive[i,j] == matrix_mkl[i,j])
            assert (matrix_naive[i,j] == matrix_tile[i,j])

    assert(matrix_naive == matrix_mkl)
    assert(matrix_naive == matrix_tile)
    assert(matrix_naive == matrix_mkl)
