#pragma once

#include <cstddef>
#include <vector>
#include <stdexcept>
#include <mkl/mkl.h>
#include <mkl/mkl_lapack.h>
#include <mkl/mkl_lapacke.h>

class Matrix {
public:
    Matrix();
    ~Matrix() {

    }

    Matrix(size_t row, size_t col) {
        this->m_row = row;
        this->m_col = col;
        size_t nelement = row * col;
        this->m_buffer = new double[nelement] {0};
    }

    double operator() (size_t row, size_t col) const {
        return this->m_buffer[this->m_col * row + col];
    }
    double& operator() (size_t row, size_t col)  {
        return this->m_buffer[this->m_col * row + col];
    }
    bool operator==(const Matrix& mat2) const {
        if (this->ncol() != mat2.m_col || this->nrow() != mat2.m_row) 
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

    const size_t& nrow() const { return m_row; }
    const size_t& ncol() const { return m_col; } 
    double *m_buffers() const { return m_buffer; }

private:
    size_t m_row;
    size_t m_col;
    double *m_buffer = nullptr;
};

// multiply naive 
Matrix multiply_naive(const Matrix& mat1, const Matrix& mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::invalid_argument("Invalid shape size, mat1 col != mat2 row.");
    }

    Matrix new_mat(mat1.nrow(), mat2.ncol());
    new_mat(0, 0) = 1;
    size_t row = mat1.nrow(), col = mat2.ncol(), mat1_col = mat1.ncol();
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
    size_t R = mat1.nrow(), C = mat2.ncol(), K = mat1.ncol();
    if (K != mat2.nrow()) {
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
    if (mat1.ncol() != mat2.nrow()) {
        throw std::invalid_argument("Invalid shape size, mat1 col != mat2 row.");
    }

    Matrix new_mat(mat1.nrow(), mat2.ncol());

    cblas_dgemm(
        CblasRowMajor, CblasNoTrans, CblasNoTrans, 
        mat1.nrow(), 
        mat2.ncol(), 
        mat1.ncol(), 
        1.0, 
        mat1.m_buffers(), 
        mat1.ncol(),
        mat2.m_buffers(), 
        mat2.ncol(), 
        0.0, 
        new_mat.m_buffers(), 
        new_mat.ncol()
    );

    return new_mat;
}


