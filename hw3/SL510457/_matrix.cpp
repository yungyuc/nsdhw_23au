#include <mkl/mkl.h>
#include <mkl/mkl_cblas.h>
#include <mkl/mkl_lapack.h>
#include <bits/stdc++.h>
#include <mkl/mkl_lapacke.h>
#include "pybind11/stl.h"
#include "pybind11/pybind11.h"
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


Matrix multiply_naive(Matrix const &mat1, Matrix const &mat2) {

    if (mat1.ncol() != mat2.nrow())
    {
        throw out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    
    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t i=0; i<ret.nrow(); ++i)
    {
        for (size_t k=0; k<ret.ncol(); ++k)
        {
            double v = 0;
            for (size_t j=0; j<mat1.ncol(); ++j)
            {
                v += mat1(i,j) * mat2(j,k);
            }
            ret(i,k) = v;
        }
    }

    return ret;

}

Matrix multiply_tile(Matrix const &mat1, Matrix const &mat2, int const tile_size) {

    if (mat1.ncol() != mat2.nrow())
    {
        throw out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    int n = mat1.nrow();
    int m = mat1.ncol();
    int p = mat2.ncol();

    Matrix ret(n, p);

    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < p; j += blockSize) {
            for (int k = 0; k < m; k += blockSize) {
                for (int ii = i; ii < min(i + blockSize, n); ++ii) {
                    for (int jj = j; jj < min(j + blockSize, p); ++jj) {
                        for (int kk = k; kk < min(k + blockSize, m); ++kk) {
                            ret(ii, jj) += mat1(ii, kk) * mat2(kk, jj);
                        }
                    }
                }
            }
        }
    }

    return ret;

}


Matrix multiply_mkl(Matrix const &mat1, Matrix const &mat2) {

    if (mat1.ncol() != mat2.nrow())
    {
        throw out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }

    mkl_set_num_threads(1);
    Matrix ret(mat1.nrow(), mat2.ncol());

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, mat1.nrow(),  mat2.ncol(), mat1.ncol(), 1.0 , mat1.data(),
     mat1.ncol(), mat2.data(), mat2.ncol(), 0.0, ret.data(), ret.ncol());

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