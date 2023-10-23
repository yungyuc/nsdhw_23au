
#include "multiply.hpp"

#ifdef UBUNTU
#include <mkl/mkl.h>
#include <mkl/mkl_lapack.h>
#include <mkl/mkl_lapacke.h>
#endif
#ifdef ARCHLINUX
#include <mkl.h>
#include <mkl_lapack.h>
#include <mkl_lapacke.h>
#endif
#include <stdexcept>

#include "Matrix.hpp"
Matrix multiply_naive(const Matrix& A, const Matrix& B) {
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

Matrix multiply_tile(const Matrix& A, const Matrix& B, size_t tsize) {
  if (A.get_cols() != B.get_rows()) {
    throw std::invalid_argument("Matrix dimensions do not match");
  }
  Matrix C(A.get_rows(), B.get_cols());
  for (size_t i = 0; i < A.get_rows(); i += tsize) {
    for (size_t j = 0; j < B.get_cols(); j += tsize) {
      for (size_t k = 0; k < A.get_cols(); k += tsize) {
        for (size_t ii = i; ii < std::min(i + tsize, A.get_rows()); ii++) {
          for (size_t jj = j; jj < std::min(j + tsize, B.get_cols()); jj++) {
            double sum = 0;
            for (size_t kk = k; kk < std::min(k + tsize, A.get_cols()); kk++) {
              sum += A(ii, kk) * B(kk, jj);
            }
            C(ii, jj) += sum;
          }
        }
      }
    }
  }
  return C;
}

Matrix multiply_mkl(const Matrix& A, const Matrix& B) {
  if (A.get_cols() != B.get_rows()) {
    throw std::invalid_argument("Matrix dimensions do not match");
  }
  Matrix C(A.get_rows(), B.get_cols());
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, A.get_rows(),
              B.get_cols(), A.get_cols(), 1, A.get_data(), A.get_cols(),
              B.get_data(), B.get_cols(), 0, C.get_data(), C.get_cols());
  return C;
}
