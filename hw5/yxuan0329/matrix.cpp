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

template <class T>
T* CustomAllocator<T>::allocate(std::size_t sz) {
    if (sz > std::numeric_limits<size_t>::max() / sizeof(T)) {
        throw std::bad_alloc();
    }
    const size_t bytesAllocated = sz * sizeof(T);

    T *ret = static_cast<T*>(malloc(bytesAllocated));
    if (ret == nullptr) throw std::bad_alloc();
    m_allocated += bytesAllocated;
    return ret; 
}

template <class T>
void CustomAllocator<T>::deallocate(T *ptr, size_t sz) {
    const size_t bytesDeallocated = sz * sizeof(T);
    m_deallocated += bytesDeallocated;
    free(ptr);
}

// Matrix from hw3
Matrix::Matrix(size_t row, size_t col) {
    this->m_row = row;
    this->m_col = col;
    this->m_buffer = std::vector<double, CustomAllocator<double>>(row * col);
}

// Matrix::~Matrix() {
//     this->m_row = 0, this->m_col = 0;
//     this->m_buffer.clear();
//     // delete[] this->m_buffer; // will cause double-free()
// }

double Matrix::operator() (size_t row, size_t col) const {
    return this->m_buffer[this->m_col * row + col];
}

double& Matrix::operator() (size_t row, size_t col) {
    return this->m_buffer[this->m_col * row + col];
}

void Matrix::resetBuffer() {
    for (size_t i=0; i<this->m_row; i++) {
        for (size_t j=0; j<this->m_col; j++) {
            this->m_buffer[i*this->m_col + j] = 0.0;
        }
    }
}

bool Matrix::operator==(const Matrix& mat2) const {
    if (this->n_col() != mat2.m_col || this->n_row() != mat2.m_row) 
        return false;
    
    int row = this->m_row, col = this->m_col;
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            size_t id = this->m_col * i + j;
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

double *Matrix::m_buffers() const { 
    return const_cast<double *>(m_buffer.data());
}

// multiply naive 
Matrix multiply_naive(const Matrix& mat1, const Matrix& mat2) {
    if (mat1.n_col() != mat2.n_row()) {
        throw std::invalid_argument("Invalid shape size, mat1 col != mat2 row.");
    }

    Matrix new_mat(mat1.n_row(), mat2.n_col());
    new_mat.resetBuffer();

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
        throw std::invalid_argument("Invalid shape size, mat1 col != mat2 row.");
    }

    Matrix new_mat(R, C);
    for (size_t row_offset=0; row_offset < R; row_offset += tile_size) {
        size_t row_size = std::min(R, row_offset+tile_size);
        
        for (size_t col_offset=0; col_offset < C; col_offset += tile_size) {
            size_t col_size = std::min(C, col_offset+tile_size);
            
            for (size_t k_offset=0; k_offset < K; k_offset += tile_size) {

                // store k in new_mat(i, j)
                size_t k_size = std::min(K, k_offset+tile_size);

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
        throw std::invalid_argument("Invalid shape size, mat1 col != mat2 row.");
    }

    Matrix new_mat(mat1.n_row(), mat2.n_col());
    new_mat.resetBuffer();

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
  m.def("allocated", &CustomAllocator<double>::getAllocated);
  m.def("deallocated", &CustomAllocator<double>::getDeallocated);
  m.def("bytes", &CustomAllocator<double>::getBytes);
  py::class_<Matrix>(m, "Matrix")
    .def(py::init<>())
    .def(py::init<size_t, size_t>())
    .def_property_readonly("nrow", [](Matrix& m){ return m.n_row(); })
    .def_property_readonly("ncol", [](Matrix& m){ return m.n_col(); })
    .def("zero", &Matrix::resetBuffer)
    .def("__eq__", &Matrix::operator==) 
    .def("__getitem__", [](Matrix& m, std::pair<size_t, size_t> idx) { return m(idx.first, idx.second); })
    .def("__setitem__", [](Matrix& m, std::pair<size_t, size_t> idx, double val) { m(idx.first, idx.second) = val; });
}
