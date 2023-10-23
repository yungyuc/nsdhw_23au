#include "multiply.hpp"

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