import pytest
import _matrix


def test_InitializeZero():
    dim = 5
    mat1 = _matrix.Matrix(dim, dim)

    assert 8 * dim * dim == _matrix.bytes()
    base_alloc = _matrix.allocated()
    base_dealloc = _matrix.deallocated()

    AllZero = True
    for r in range(dim):
        for c in range(dim):
            if mat1[r, c] != 0.0:
                AllZero = False
                break
        if AllZero != True:
            break
    assert AllZero

    assert 8 * dim * dim == _matrix.bytes()
    assert base_alloc == _matrix.allocated()
    assert base_dealloc == _matrix.deallocated()


def test_InitializeVector():
    dim = 2
    mat2 = _matrix.Matrix(dim, dim, [0.0, 0.1, 1.0, 1.1])

    assert 8 * dim * dim == _matrix.bytes()
    base_alloc = _matrix.allocated()
    base_dealloc = _matrix.deallocated()

    assert mat2[0, 0] == 0.0
    assert mat2[0, 1] == 0.1
    assert mat2[1, 0] == 1.0
    assert mat2[1, 1] == 1.1

    assert 8 * dim * dim == _matrix.bytes()
    assert base_alloc == _matrix.allocated()
    assert base_dealloc == _matrix.deallocated()


def test_SameResult():
    assert 0 == _matrix.bytes()

    dim = 1200
    mat1 = _matrix.Matrix(dim, dim)
    mat2 = _matrix.Matrix(dim, dim)

    assert 2 * 8 * dim * dim == _matrix.bytes()
    base_alloc = _matrix.allocated()
    base_dealloc = _matrix.deallocated()

    for it in range(dim):
        for jt in range(dim):
            mat1[it, jt] = it * dim + jt + 1
            mat2[it, jt] = it * dim + jt + 1
    
    ret_naive = _matrix.multiply_naive(mat1, mat2)
    ret_mkl = _matrix.multiply_mkl(mat1, mat2)

    for i in range(dim):
        for j in range(dim):
            assert ret_naive[i,j] == ret_mkl[i,j]
    # assert ret_mkl == ret_naive

    assert 4 * 8 * dim * dim == _matrix.bytes()
    assert base_alloc + 2 * 8 * dim * dim == _matrix.allocated()
    assert base_dealloc == _matrix.deallocated()


def test_memory():

    assert 0 == _matrix.bytes()
    base_alloc = _matrix.allocated()
    base_dealloc = _matrix.deallocated()

    dim = 100
    mat1 = _matrix.Matrix(dim, dim)
    mat2 = _matrix.Matrix(dim, dim)
    mat3 = _matrix.Matrix(dim, dim)
    assert 3 * 8 * dim * dim == _matrix.bytes()
    assert base_alloc + 3 * 8 * dim * dim == _matrix.allocated()
    assert base_dealloc == _matrix.deallocated()

    mat1 = mat2 = mat3 = None
    assert 0 == _matrix.bytes()
    assert base_alloc + 3 * 8 * dim * dim == _matrix.allocated()
    assert base_dealloc + 3 * 8 * dim * dim == _matrix.deallocated()


if __name__ == '__main__':
    pytest.main()