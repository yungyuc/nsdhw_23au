#include "Matrix.hpp"

#include <cstring>
#include <iostream>
Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
  data = new double[rows * cols];
  std::memset(data, 0, rows * cols * sizeof(double));
}

double& Matrix::operator()(size_t i, size_t j) const {
  return data[i * cols + j];
}

const size_t Matrix::get_rows() const { return rows; }

const size_t Matrix::get_cols() const { return cols; }
