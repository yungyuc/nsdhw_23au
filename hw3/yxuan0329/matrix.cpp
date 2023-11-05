#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <cstddef>
#include <mkl/mkl.h>
#include <mkl/mkl_lapack.h>
#include <mkl/mkl_lapacke.h>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include "matrix.h"

using namespace std;

Matrix::Matrix() {
    this->m_row = 0;
    this->m_col = 0;
    this->m_buffer = NULL;
}
    
Matrix::Matrix(size_t row, size_t col, vector<double> const value) {
    this->m_row = row;
    this->m_col = col;
    size_t nelement = row * col;
    this->m_buffer = new double[nelement];
    int cnt = 0;
    // this->m_buffer = (double*)malloc(sizeof(double) * value.size());
    // memset(this->m_buffer, 0, sizeof(double) * value.size());

    for (const double&v : value) {
        this->m_buffer[cnt++] = v;
    }
}

Matrix::Matrix(size_t row, size_t col) {
    this->m_row = row;
    this->m_col = col;
    size_t nelement = row * col;
    this->m_buffer = new double[nelement] {0};
}

Matrix::~Matrix() {
    this->m_row = 0, this->m_col = 0;
    // delete[] this->m_buffer; // will cause double-free()
}

double Matrix::operator() (size_t row, size_t col) const {
    return this->m_buffer[this->m_col * row + col];
}

double& Matrix::operator() (size_t row, size_t col) {
    return this->m_buffer[this->m_col * row + col];
}

Matrix Matrix::transpose() const {
    int row = this->m_row, col = this->m_col; 
    Matrix new_mat(col, row);

    for (int i=0; i<col; i++) {
        for (int j=0; j<row; j++) {
            size_t id = this->m_col * i + j;
            new_mat(j, i) = this->m_buffer[id];
        }
    }
    return new_mat;
}


bool Matrix::operator==(const Matrix& mat2) const {
    if (this->n_col() != mat2.m_col || this->n_row() != mat2.m_row) 
        return false;
    
    int row = this->m_row, col = this->m_col;
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            size_t id = this->m_col * i + j;
            // cout << i <<" " << j << " " << this->m_buffer[id] - mat2(i, j) << " " << this->m_buffer[id] << " " << mat2(i, j) << endl;
            if (this->m_buffer[id] != mat2(i, j)) {
                return false;
            }
            
        }
    }
    return true;
}

bool Matrix::operator != (const Matrix& mat2) const {
    return !(*this == mat2);
}

const size_t& Matrix::n_row() const {
    return this->m_row;
}

const size_t& Matrix::n_col() const {
    return this->m_col;
}

// multiply naive 
Matrix multiply_naive(const Matrix& mat1, const Matrix& mat2) {
    if (mat1.n_col() != mat2.n_row()) {
        throw invalid_argument("Invalid shape size, mat1 col != mat2 row.");
    }

    Matrix new_mat(mat1.n_row(), mat2.n_col());
    new_mat(0, 0) = 1;
    size_t row = mat1.n_row(), col = mat2.n_col(), mat1_col = mat1.n_col();
    for (size_t i=0; i<row; i++) {
        for (size_t j=0; j<col; j++) {
            new_mat(i, j) = 0;
            for (size_t k=0; k<mat1_col; k++) {
                new_mat(i, j) += mat1(i, k) * mat2(k, j);
            }
            // cout << new_mat(i, j) << " ";
        }
        // cout << endl;
    }
    return new_mat;
}

// multiply tile 
Matrix multiply_tile(const Matrix& mat1, const Matrix& mat2, size_t tile_size) {
    size_t R = mat1.n_row(), C = mat2.n_col(), K = mat1.n_col();
    if (K != mat2.n_row()) {
        throw invalid_argument("Invalid shape size, mat1 col != mat2 row.");
    }

    Matrix new_mat(R, C);
    for (size_t row_offset=0; row_offset < R; row_offset += tile_size) {
        size_t row_size = min(R, row_offset+tile_size);
        
        for (size_t col_offset=0; col_offset < C; col_offset += tile_size) {
            size_t col_size = min(C, col_offset+tile_size);
            
            for (size_t k_offset=0; k_offset < K; k_offset += tile_size) {

                // store k in new_mat(i, j)
                size_t k_size = min(K, k_offset+tile_size);

                for (size_t i=row_offset; i<row_size; i++){
                    for (size_t j=col_offset; j<col_size; j++) {
                        double k_sum = 0;
                        for (size_t k=k_offset; k<k_size; k++) {
                            k_sum += mat1(i, k) * mat2(k, j);
                        }
                        new_mat(i, j) += k_sum;
                    }
                } // finish storing k in new_mat(i, j)
            }
        }
    }
    return new_mat;
}

// multiply mkl
Matrix multiply_mkl(const Matrix& mat1, const Matrix& mat2) {
    if (mat1.n_col() != mat2.n_row()) {
        throw invalid_argument("Invalid shape size, mat1 col != mat2 row.");
    }

    Matrix new_mat(mat1.n_row(), mat2.n_col());

    cblas_dgemm(
        CblasRowMajor, CblasNoTrans, CblasNoTrans, 
        mat1.n_row(), 
        mat2.n_col(), 
        mat1.n_col(), 
        1.0, 
        mat1.m_buffers(), 
        mat1.n_col(),
        mat2.m_buffers(), 
        mat2.n_col(), 
        0.0, 
        new_mat.m_buffers(), 
        new_mat.n_col()
    );

    return new_mat;
}


// pybind11
namespace py = pybind11;

PYBIND11_MODULE(_matrix, m) {
  m.doc() = "Matrix multiplication function implementation";      // module doc string
  m.def("multiply_naive", &multiply_naive);
  m.def("multiply_tile", &multiply_tile);
  m.def("multiply_mkl", &multiply_mkl);
  py::class_<Matrix>(m, "Matrix")
    .def(py::init<>())
    .def(py::init<size_t, size_t>())
    .def_property_readonly("nrow", [](Matrix& m){ return m.n_row(); })
    .def_property_readonly("ncol", [](Matrix& m){ return m.n_col(); })
    .def("__eq__", &Matrix::operator==) 
    .def("__getitem__", [](Matrix& m, std::pair<size_t, size_t> idx) { return m(idx.first, idx.second); })
    .def("__setitem__", [](Matrix& m, std::pair<size_t, size_t> idx, double val) { m(idx.first, idx.second) = val; });
}
