#include "pybind11/pybind11.h"
#include <mkl/mkl.h>
#include <mkl/mkl_cblas.h>
#include "pybind11/stl.h"
#include <mkl/mkl_lapack.h>
#include <bits/stdc++.h>
#include <mkl/mkl_lapacke.h>
#include "pybind11/operators.h"

using namespace std;
namespace py = pybind11;

class Matrix {

public:

    Matrix(int rows, int cols) : m_rows(rows), m_cols(cols), m_data(new double[rows*cols]){
        memset(m_data, 0, sizeof(double)*rows*cols);
    }
    Matrix(const Matrix &m) : m_cols(m.ncol()), m_rows(m.nrow()){
        m_data = new double[m_rows*m_cols];
        for (int i = 0; i < m_rows; i++){
            for (int j = 0; j < m_cols; j++){
                m_data[i*m_cols+j] = m(i, j);
            }
        }
    }

    ~Matrix(){
        delete[] m_data;
    }
    double &operator()(int x, int y){
        return m_data[y*m_cols+x];
    }
    double operator()(int x, int y) const{
        return m_data[y*m_cols+x];
    }
    bool operator ==(const Matrix &m) const{
        if (m_rows != m.nrow() || m_cols != m.ncol()){
            return false;
        }
        for (int i = 0; i < m_rows; i++){
            for (int j = 0; j < m_cols; j++){
                if ((*this)(i, j) != m(i, j)){
                    return false;
                }
            }
        }
        return true;
    }
    int nrow() const{ 
        return m_rows; 
    }
    int ncol() const{ 
        return m_cols;
    }
    double* data() const{
        return m_data;
    }

private:
    int m_rows;
    int m_cols;
    double *m_data;
};


Matrix multiply_naive(Matrix const &m1, Matrix const &m2){
    Matrix ret(m1.nrow(), m2.ncol());
    for (int i = 0; i < m1.nrow(); i++) {
        for (int j = 0; j < m2.ncol(); j++) {
            double sum = 0.0;
            for (int k = 0; k < m1.ncol(); k++) {
                sum += m1(i, k) * m2(k, j);
            }
            ret(i, j) = sum;
        }
    }
    return ret;
}

Matrix multiply_tile(Matrix const &m1, Matrix const &m2, int const tile_size){
    int m = m1.nrow();
    int n = m2.ncol();
    int k = m1.ncol();

    Matrix ret(m, n);
    for (int i0 = 0; i0 < m; i0 += tile_size) {
        int imax = std::min(i0 + tile_size, m);
        for (int j0 = 0; j0 < n; j0 += tile_size) {
            int jmax = std::min(j0 + tile_size, n);
            for (int k0 = 0; k0 < k; k0 += tile_size) {
                int kmax = std::min(k0 + tile_size, k);
                for (int i = i0; i < imax; i++) {
                    for (int j = j0; j < jmax; j++) {
                        for (int l = k0; l < kmax; l++) {
                            ret(i, j) += m1(i, l) * m2(l, j);
                        }
                    }
                }
            }
        }
    }

    return ret;

}


Matrix multiply_mkl(Matrix const &m1, Matrix const &m2){
    mkl_set_num_threads(1);
    Matrix ret(m1.nrow(), m2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m1.nrow(),  m2.ncol(), m1.ncol(), 1.0 , m1.data(),
     m1.ncol(), m2.data(), m2.ncol(), 0.0, ret.data(), ret.ncol());
    return ret;
}



PYBIND11_MODULE(_matrix, m){
    m.doc() = "matrix-matrix multiplication";
    m.def("multiply_naive", &multiply_naive, "naive");
    m.def("multiply_tile", &multiply_tile, "tile");
    m.def("multiply_mkl", &multiply_mkl, "mkl");
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<int, int>())
        .def_property_readonly("nrow", [](const Matrix &mat) { return mat.nrow(); })
        .def_property_readonly("ncol", [](const Matrix &mat) { return mat.ncol(); })
        .def("__eq__", [](const Matrix &a, const Matrix &b) { 
            return a == b; })
        .def("__setitem__", [](Matrix &self, std::pair<int, int> idx, double val) {
            self(idx.first, idx.second) = val;
        })
        .def("__getitem__", [](const Matrix &self, std::pair<int, int> idx) {
            return self(idx.first, idx.second);
        });
}