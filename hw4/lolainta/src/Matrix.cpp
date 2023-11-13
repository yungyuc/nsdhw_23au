#include "Matrix.hpp"

#include <cstring>
#include <iostream>
Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
  data.assign(rows * cols, 0);
}

double& Matrix::operator()(size_t i, size_t j) { return data[i * cols + j]; }

double* Matrix::get_data() { return data.data(); }

const double& Matrix::operator()(size_t i, size_t j) const {
  return data[i * cols + j];
}

const double* Matrix::get_data() const { return data.data(); }

const size_t Matrix::get_rows() const { return rows; }

const size_t Matrix::get_cols() const { return cols; }

bool Matrix::operator==(const Matrix& other) const {
  if (rows != other.rows || cols != other.cols) {
    return false;
  }
  for (size_t i = 0; i < rows * cols; i++) {
    if (data[i] != other.data[i]) {
      return false;
    }
  }
  return true;
}