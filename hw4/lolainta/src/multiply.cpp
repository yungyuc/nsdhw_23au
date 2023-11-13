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
#include "multiply.hpp"

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
  auto m = A.get_rows();
  auto n = B.get_cols();
  auto k = A.get_cols();
  Matrix C(A.get_rows(), B.get_cols());
  for (size_t i = 0; i < m; i += tsize)
    for (size_t j = 0; j < n; j += tsize)
      for (size_t l = 0; l < k; l += tsize)
        for (size_t ii = i; ii < std::min(i + tsize, m); ii++)
          for (size_t jj = j; jj < std::min(j + tsize, n); jj++) {
            double sum = 0;
            for (size_t ll = l; ll < std::min(l + tsize, k); ll++)
              sum += A(ii, ll) * B(ll, jj);
            C(ii, jj) += sum;
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
