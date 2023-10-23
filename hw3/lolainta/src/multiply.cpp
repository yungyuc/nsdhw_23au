#include "multiply.hpp"

#include <mkl/mkl.h>
#include <mkl/mkl_lapack.h>
#include <mkl/mkl_lapacke.h>

#include <stdexcept>

Matrix Multiply::multiply_naive(const Matrix& A, const Matrix& B) {
  if (A.get_cols() != B.get_rows()) {
    throw std::invalid_argument("Matrix dimensions do not match");
  }
  Matrix C(A.get_rows(), B.get_cols());
  for (size_t i = 0; i < A.get_rows(); i++) {
    for (size_t j = 0; j < B.get_cols(); j++) {
      for (size_t k = 0; k < A.get_cols(); k++) {
        C(i, j) += A(i, k) * B(k, j);
      }
    }
  }
  return C;
}

Matrix Multiply::multiply_tile(const Matrix& A, const Matrix& B,
                               size_t tile_size) {
  if (A.get_cols() != B.get_rows()) {
    throw std::invalid_argument("Matrix dimensions do not match");
  }
  Matrix C(A.get_rows(), B.get_cols());
  for (size_t i = 0; i < A.get_rows(); i += tile_size) {
    for (size_t j = 0; j < B.get_cols(); j += tile_size) {
      for (size_t k = 0; k < A.get_cols(); k += tile_size) {
        for (size_t ii = i; ii < std::min(i + tile_size, A.get_rows()); ii++) {
          for (size_t jj = j; jj < std::min(j + tile_size, B.get_cols());
               jj++) {
            for (size_t kk = k; kk < std::min(k + tile_size, A.get_cols());
                 kk++) {
              C(ii, jj) += A(ii, kk) * B(kk, jj);
            }
          }
        }
      }
    }
  }
  return C;
}

Matrix Multiply::multiply_mkl(const Matrix& A, const Matrix& B) {
  if (A.get_cols() != B.get_rows()) {
    throw std::invalid_argument("Matrix dimensions do not match");
  }
  Matrix C(A.get_rows(), B.get_cols());
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, A.get_rows(),
              B.get_cols(), A.get_cols(), 1, A.data[0], A.get_cols(), B.data[0],
              B.get_cols(), 0, C.data[0], C.get_cols());
  return C;
}
