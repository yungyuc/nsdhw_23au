import time
import pytest
import _matrix

def test_matrix():
    size = [50, 1000]
    f = open("performance.txt", "a")
    for s in size:
        f.write("size: " + str(s) + "\n")
        m1 = _matrix.Matrix(s, s)
        m2 = _matrix.Matrix(s, s)
        for i in range(s):
            for j in range(s):
                m1[i, j] = i+j
                m2[i, j] = i+j

        f.write("mkl:\n")
        start = time.time()
        golden = _matrix.multiply_mkl(m1, m2)
        end = time.time()
        f.write(str(end-start) + "\n")

        f.write("naive:\n")
        start = time.time()
        m3 = _matrix.multiply_naive(m1, m2)
        end = time.time()
        f.write(str(end-start) + "\n")
        naivetime = end-start
        assert m3.nrow == golden.nrow
        assert m3.ncol == golden.ncol
        for i in range(m3.nrow):
            for j in range(m3.ncol):
                assert m3[i, j] == golden[i, j]

        f.write("tile:\n")
        start = time.time()
        m3 = _matrix.multiply_tile(m1, m2, 32)
        end = time.time()
        f.write(str(end-start) + "\n")
        tiletime = end-start
        f.write("speedup(naive time/tile time): " + str(naivetime/tiletime) + "\n")

        assert m3.nrow == golden.nrow
        assert m3.ncol == golden.ncol
        for i in range(m3.nrow):
            for j in range(m3.ncol):
                assert m3[i, j] == golden[i, j]




if __name__ == '__main__':
	test_matrix()