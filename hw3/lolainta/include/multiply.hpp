#pragma once
#include <cstddef>

#include "Matrix.hpp"

namespace Multiply {
Matrix multiply_naive(const Matrix&, const Matrix&);
Matrix multiply_tile(const Matrix&, const Matrix&, size_t);
Matrix multiply_mkl(const Matrix&, const Matrix&);
}  // namespace Multiply
