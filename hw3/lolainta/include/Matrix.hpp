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
  const size_t get_rows() const;
  const size_t get_cols() const;
  friend Multiply::Matrix Multiply::multiply_naive(const Multiply::Matrix&,
                                                   const Multiply::Matrix&);
  friend Multiply::Matrix Multiply::multiply_tile(const Multiply::Matrix&,
                                                  const Multiply::Matrix&,
                                                  size_t);
  friend Multiply::Matrix Multiply::multiply_mkl(const Multiply::Matrix&,
                                                 const Multiply::Matrix&);
};
