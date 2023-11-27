import _matrix
import pytest

@pytest.fixture
def make_matrices():
    def _make_matrices(size):
        mat1 = _matrix.Matrix(size, size)
        mat2 = _matrix.Matrix(size, size)
        mat3 = _matrix.Matrix(size, size)

        for it in range(size):
            for jt in range(size):
                mat1[it, jt] = it * size + jt + 1
                mat2[it, jt] = it * size + jt + 1
                mat3[it, jt] = 0

        return mat1, mat2, mat3
    return _make_matrices

def test_basic(make_matrices):
    assert _matrix.bytes() == 0

    size = 100
    mat1, mat2, mat3, *_ = make_matrices(size)
    assert _matrix.bytes() == 3 * 8 * size * size
    base_alloc = _matrix.allocated()
    base_dealloc = _matrix.deallocated()

    assert size == mat1.nrow
    assert size == mat1.ncol
    assert size == mat2.nrow
    assert size == mat2.ncol
    assert size == mat3.nrow
    assert size == mat3.ncol

    assert mat1[0, 1] == 2
    assert mat1[1, 1] == size + 2
    assert mat1[1, size - 1] == size * 2
    assert mat1[size - 1, size - 1] == size * size

    for i in range(mat1.nrow):
        for j in range(mat1.ncol):
            assert mat1[i, j] != 0
            assert mat1[i, j] == mat2[i, j]
            assert mat3[i, j] == 0

    assert mat1 == mat2
    assert mat1 is not mat2

    assert _matrix.bytes() == 3 * 8 * size * size
    assert base_alloc == _matrix.allocated()
    assert base_dealloc == _matrix.deallocated()

def test_match_naive_mkl(make_matrices):
    assert _matrix.bytes() == 0

    size = 100
    mat1, mat2, *_ = make_matrices(size)
    assert _matrix.bytes() == 3 * 8 * size * size
    base_alloc = _matrix.allocated()
    base_dealloc = _matrix.deallocated()

    ret_naive = _matrix.multiply_naive(mat1, mat2)
    ret_mkl = _matrix.multiply_mkl(mat1, mat2)

    assert size == ret_naive.nrow
    assert size == ret_naive.ncol
    assert size == ret_mkl.nrow
    assert size == ret_mkl.ncol

    for i in range(ret_naive.nrow):
        for j in range(ret_naive.ncol):
            assert mat1[i, j] != ret_mkl[i, j]
            assert ret_naive[i, j] == ret_mkl[i, j]

    assert _matrix.bytes() == 5 * 8 * size * size
    assert base_alloc + 2 * 8 * size * size == _matrix.allocated()
    assert base_dealloc == _matrix.deallocated()

def test_zero(make_matrices):
    assert _matrix.bytes() == 0

    size = 200
    mat1, mat2, mat3, *_ = make_matrices(size)
    assert _matrix.bytes() == 3 * 8 * size * size
    base_alloc = _matrix.allocated()
    base_dealloc = _matrix.deallocated()

    ret_naive = _matrix.multiply_naive(mat1, mat3)
    ret_mkl = _matrix.multiply_mkl(mat1, mat3)

    assert size == ret_naive.nrow
    assert size == ret_naive.ncol
    assert size == ret_mkl.nrow
    assert size == ret_mkl.ncol

    for i in range(ret_naive.nrow):
        for j in range(ret_naive.ncol):
            assert ret_naive[i, j] == 0
            assert ret_mkl[i, j] == 0

    assert _matrix.bytes() == 5 * 8 * size * size
    assert base_alloc + 2 * 8 * size * size == _matrix.allocated()
    assert base_dealloc == _matrix.deallocated()

def test_memory(make_matrices):
    assert _matrix.bytes() == 0
    base_alloc = _matrix.allocated()
    base_dealloc = _matrix.deallocated()

    size = 100
    mat1, mat2, mat3, *_ = make_matrices(size)
    assert _matrix.bytes() == 3 * 8 * size * size
    assert base_alloc + 3 * 8 * size * size == _matrix.allocated()
    assert base_dealloc == _matrix.deallocated()

    mat1 = mat2 = mat3 = None
    assert _matrix.bytes() == 0
    assert base_dealloc + 3 * 8 * size * size == _matrix.deallocated()
    assert base_alloc + 3 * 8 * size * size == _matrix.allocated()
