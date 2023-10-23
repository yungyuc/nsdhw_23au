#pragma once
#include <cstddef>
class Matrix {
 private:
  size_t rows;
  size_t cols;
  double** data;
 public:
  Matrix(size_t rows, size_t cols);
  ~Matrix() = default;
  double& operator()(size_t, size_t) const;
  const size_t get_rows() const;
  const size_t get_cols() const;
};