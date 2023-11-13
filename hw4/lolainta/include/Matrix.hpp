#pragma once
#include <cstddef>
#include <vector>

#include "CustomAllocator.hpp"
#include "multiply.hpp"

class Matrix {
 public:
  Matrix() = delete;
  Matrix(size_t rows, size_t cols);
  Matrix(Matrix&&);
  Matrix(const Matrix&);
  ~Matrix();

  double& operator()(size_t, size_t);
  const double& operator()(size_t, size_t) const;

  double* get_data();
  const double* get_data() const;

  const size_t get_rows() const;
  const size_t get_cols() const;
  bool operator==(const Matrix&) const;
  bool operator!=(const Matrix&) const;

 private:
  size_t rows;
  size_t cols;
  std::vector<double, CustomAllocator<double>> data;
};
