#include <iostream>
#include <mkl.h>
#include <pybind11/pybind11.h>
using namespace std;
namespace py = pybind11;

class Matrix {
public:
    Matrix(size_t nrow, size_t ncol): m_nrow(nrow), m_ncol(ncol) {
        size_t nelement = nrow * ncol;
        m_data = new double[nelement];
    }
    ~Matrix() {delete[] m_data;}
    Matrix(const Matrix &matrix) {
        m_nrow = matrix.m_nrow;
        m_ncol = matrix.m_ncol;
        m_data = new double[m_nrow * m_ncol](); 
        memcpy(m_data, matrix.m_data, m_nrow * m_ncol*sizeof(double));
    }
    bool operator == (Matrix const &matrix) const {
        for (size_t i = 0; i < m_nrow; i++) 
            for (size_t j = 0; j < m_ncol; j++)
                if (m_data[i*m_ncol + j] != matrix(i, j)) 
                    return false;
        return true;
    }
    Matrix& operator= (const Matrix& matrix) {
        m_data = matrix.m_data;
        return *this;
    }
    double operator()(size_t row, size_t col) const {return m_data[row * m_ncol + col];}
    double& operator()(size_t row, size_t col) {return m_data[row * m_ncol + col];}
    double* get_data() const {return m_data;}
    size_t nrow() const {return m_nrow;}
    size_t ncol() const {return m_ncol;}

private:
    size_t m_nrow;
    size_t m_ncol;
    double* m_data;
};

void setZero(Matrix& mat) {
    size_t n = mat.nrow();
    size_t m = mat.ncol();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            mat(i, j) = 0.0;
        }
    }
}

void generateValue(Matrix& mat) {
    size_t n = mat.nrow();
    size_t m = mat.ncol();
    double val;
    for (size_t i = 0 ; i < n ; i++){
        for (size_t j = 0 ; j < m ; j++){
            val = rand() % 10;
            mat(i, j) = val;
        }
    }
}

Matrix multiply_naive(Matrix const & mat1, Matrix const & mat2) {
    if (mat1.ncol() != mat2.nrow()) throw out_of_range("matrices cannot be multiplied");
    size_t n = mat1.nrow();
    size_t m = mat1.ncol();
    size_t p = mat2.ncol();
    Matrix naive_mat(n, p);
    double val;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < p; j++) {
            val = 0.0;
            for (size_t k = 0; k < m; k++) {
                val += mat1(i, k) * mat2(k, j);
            }
            naive_mat(i, j) = val;
        }
    }
    return naive_mat;
}

Matrix multiply_tile(Matrix& mat1, Matrix& mat2, size_t tile_size) {
    if (mat1.ncol() != mat2.nrow()) throw out_of_range("matrices cannot be multiplied");
    size_t n = mat1.nrow();
    size_t m = mat1.ncol();
    size_t p = mat2.ncol();
    Matrix tile_mat(n, p);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < p; ++j) {
            tile_mat(i, j) = 0.0;
        }
    }
    double val;
    for (size_t i = 0; i < n; i += tile_size) {
        for (size_t j = 0; j < p; j += tile_size) {
            for (size_t k = 0; k < m; k += tile_size) {
                for (size_t ii = i; ii < min(i + tile_size, n); ii++) {
                    for (size_t jj = j; jj < min(j + tile_size, p); jj++) {
                        val = 0.0;
                        for (size_t kk = k; kk < min(k + tile_size, m); kk++) {
                            val += mat1(ii, kk) * mat2(kk, jj);
                        }
                        tile_mat(ii, jj) += val;
                    }
                }
            }
        }
    }
    return tile_mat;
}

Matrix multiply_mkl(const Matrix& mat1, const Matrix& mat2) {
    if (mat1.ncol() != mat2.nrow()) throw out_of_range("matrices cannot be multiplied");
    Matrix MKL_mat(mat1.nrow(), mat2.ncol());
    cblas_dgemm(
        CblasRowMajor, 
        CblasNoTrans, 
        CblasNoTrans, 
        mat1.nrow(), 
        mat2.ncol(), 
        mat1.ncol(), 
        1.0, 
        mat1.get_data(), 
        mat1.ncol(), 
        mat2.get_data(), 
        mat2.ncol(), 
        0.0, 
        MKL_mat.get_data(), 
        mat2.ncol());
    return MKL_mat;
}

PYBIND11_MODULE(_matrix, m) {
    m.doc() = "Matrix multiply";
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
    m.def("generateValue", &generateValue);
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def(py::init<const Matrix &>())
        .def_property_readonly("nrow", [](const Matrix &mat){ return mat.nrow();})
        .def_property_readonly("ncol", [](const Matrix &mat){ return mat.ncol();})
        .def("assign", &Matrix::operator=)
        .def("__eq__", [](const Matrix &mat, const Matrix &other) { return mat == other;})
        .def("__getitem__", [](const Matrix &m, pair<size_t, size_t> idx) {return m(idx.first, idx.second);})
        .def("__setitem__", [](Matrix &m, pair<size_t, size_t> idx, double value) {m(idx.first, idx.second) = value;});
}