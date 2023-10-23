#pragma once
#include <cstddef>

#include "multiply.hpp"

class Matrix {
 private:
  size_t rows;
  size_t cols;
  double* data;

 public:
  Matrix() = delete;
  Matrix(size_t rows, size_t cols);
  ~Matrix() = default;
  double& operator()(size_t, size_t) const;
  double* get_data() const;
  const size_t get_rows() const;
  const size_t get_cols() const;
  friend Matrix multiply_naive(const Matrix&, const Matrix&);
  friend Matrix multiply_tile(const Matrix&, const Matrix&, size_t);
  friend Matrix multiply_mkl(const Matrix&, const Matrix&);
};
