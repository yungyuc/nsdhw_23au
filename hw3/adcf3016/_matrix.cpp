#include <bits/stdc++.h>
#include <mkl/mkl.h>
#include <pybind11/pybind11.h>

class Matrix {
   public:
    Matrix(int row, int col) : m_row(row), m_col(col), m_key(new double[row * col]) {
        memset(m_key, 0, sizeof(double) * row * col);
    }

    int nrow() const {
        return m_row;
    }

    int ncol() const {
        return m_col;
    }

    double& operator()(int x, int y) {
        return m_key[x * m_col + y];
    }

    double operator()(int x, int y) const {
        return m_key[x * m_col + y];
    }

    bool operator==(const Matrix& mat) const {
        if (mat.m_col != this->m_col || mat.m_row != this->m_row) {
            return false;
        }
        for (int i = 0; i < this->m_row; i++) {
            for (int j = 0; j < this->m_col; j++) {
                if ((*this)(i, j) != mat(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    double* get_key() const {
        return m_key;
    }

   private:
    int m_row;
    int m_col;
    double* m_key;
};

Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2) {
    assert(mat1.ncol() == mat2.nrow());

    Matrix output(mat1.nrow(), mat2.ncol());
    for (int i = 0; i < mat1.nrow(); i++) {
        for (int j = 0; j < mat2.ncol(); j++) {
            double sum = 0;
            for (int k = 0; k < mat1.ncol(); k++) {
                sum += mat1(i, k) * mat2(k, j);
            }
            output(i, j) = sum;
        }
    }
    return output;
}

Matrix multiply_tile(Matrix const& mat1, Matrix const& mat2, int tile_size) {
    assert(mat1.ncol() == mat2.nrow());

    Matrix output(mat1.nrow(), mat2.ncol());
    for (int i = 0; i < mat1.nrow(); i += tile_size) {
        for (int j = 0; j < mat2.ncol(); j += tile_size) {
            for (int k = 0; k < mat1.ncol(); k += tile_size) {
                for (int ii = i; ii < std::min(i + tile_size, mat1.nrow()); ii++) {
                    for (int jj = j; jj < std::min(j + tile_size, mat2.ncol()); jj++) {
                        for (int kk = k; kk < std::min(k + tile_size, mat1.ncol()); kk++) {
                            output(ii, jj) += mat1(ii, kk) * mat2(kk, jj);
                        }
                    }
                }
            }
        }
    }

    return output;
}

Matrix multiply_mkl(Matrix const& mat1, Matrix const& mat2) {
    assert(mat1.ncol() == mat2.nrow());

    Matrix output(mat1.nrow(), mat2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mat1.nrow(), mat1.ncol(), mat2.ncol(), 1, mat1.get_key(), mat1.ncol(), mat2.get_key(), mat2.ncol(), 0, output.get_key(), mat2.ncol());
    return output;
}

PYBIND11_MODULE(_matrix, m) {
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<int, int>())
        .def_property_readonly("nrow", [](const Matrix& mat) { return mat.nrow(); })
        .def_property_readonly("ncol", [](const Matrix& mat) { return mat.ncol(); })
        .def("__eq__", [](const Matrix& a, const Matrix& b) { return a == b; })
        .def("__setitem__", [](Matrix& self, std::pair<int, int> idx, double val) {
            self(idx.first, idx.second) = val;
        })
        .def("__getitem__", [](const Matrix& self, std::pair<int, int> idx) {
            return self(idx.first, idx.second);
        });
}
