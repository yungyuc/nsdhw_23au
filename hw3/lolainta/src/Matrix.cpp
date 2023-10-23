#include "Matrix.hpp"

#include <cstring>
#include <iostream>
Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
  data = new double*[rows];
  for (size_t i = 0; i < rows; i++) {
    data[i] = new double[cols];
  }
  for (size_t i = 0; i < rows; i++) {
    std::memset(data[i], 0, cols * sizeof(double));
  }
}

double& Matrix::operator()(size_t i, size_t j) const { return data[i][j]; }

const size_t Matrix::get_rows() const { return rows; }

const size_t Matrix::get_cols() const { return cols; }