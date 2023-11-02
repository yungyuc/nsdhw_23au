#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <cblas.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

namespace py = pybind11;

class LinearMatrix {
private:
    std::vector<double> data_;
    size_t rows_, cols_;

public:
    LinearMatrix(size_t rows, size_t cols) : rows_(rows), cols_(cols), data_(rows * cols, 0.0) {}

    double at(size_t row, size_t col) const {
        return data_[row * cols_ + col];
    }

    double& at(size_t row, size_t col) {
        return data_[row * cols_ + col];
    }

    size_t row_count() const { return rows_; }
    size_t col_count() const { return cols_; }
    size_t total_size() const { return data_.size(); }

    // Accessor for the data buffer
    double* buffer() {
        return data_.data();
    }

    const double* buffer() const {
        return data_.data();
    }
};

LinearMatrix naive_multiplication(const LinearMatrix& A, const LinearMatrix& B) {
    if (A.col_count() != B.row_count())
        throw std::out_of_range("Matrix dimensions do not match for multiplication");

    LinearMatrix result(A.row_count(), B.col_count());
    for (size_t i = 0; i < A.row_count(); ++i) {
        for (size_t j = 0; j < B.col_count(); ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < A.col_count(); ++k) {
                sum += A.at(i, k) * B.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}

LinearMatrix tiled_multiplication(const LinearMatrix& A, const LinearMatrix& B, size_t block_size) {
    if (A.col_count() != B.row_count())
        throw std::out_of_range("Matrix dimensions do not match for multiplication");

    LinearMatrix result(A.row_count(), B.col_count());
    for (size_t i = 0; i < A.row_count(); i += block_size) {
        for (size_t j = 0; j < B.col_count(); j += block_size) {
            for (size_t k = 0; k < A.col_count(); k += block_size) {
                for (size_t ii = i; ii < std::min(i + block_size, A.row_count()); ++ii) {
                    for (size_t jj = j; jj < std::min(j + block_size, B.col_count()); ++jj) {
                        for (size_t kk = k; kk < std::min(k + block_size, A.col_count()); ++kk) {
                            result.at(ii, jj) += A.at(ii, kk) * B.at(kk, jj);
                        }
                    }
                }
            }
        }
    }
    return result;
}

LinearMatrix mkl_multiplication(const LinearMatrix& A, const LinearMatrix& B) {
    if (A.col_count() != B.row_count())
        throw std::out_of_range("Matrix dimensions do not match for multiplication");

    LinearMatrix result(A.row_count(), B.col_count());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                A.row_count(), B.col_count(), A.col_count(), 
                1.0, A.buffer(), A.col_count(), 
                B.buffer(), B.col_count(), 
                0.0, result.buffer(), result.col_count());

    return result;
}

PYBIND11_MODULE(_matrix, m) {
    m.def("multiply_naive", &naive_multiplication);
    m.def("multiply_tile", &tiled_multiplication);
    m.def("multiply_mkl", &mkl_multiplication);

    py::class_<LinearMatrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def("at", static_cast<double&(LinearMatrix::*)(size_t, size_t)>(&LinearMatrix::at), py::return_value_policy::reference_internal)
        .def("at", static_cast<double(LinearMatrix::*)(size_t, size_t) const>(&LinearMatrix::at))
        .def("row_count", &LinearMatrix::row_count)
        .def("col_count", &LinearMatrix::col_count)
        .def("total_size", &LinearMatrix::total_size)
        .def("__getitem__", [](const LinearMatrix &m, std::pair<size_t, size_t> idx) {
            return m.at(idx.first, idx.second);
        })
        .def("__setitem__", [](LinearMatrix &m, std::pair<size_t, size_t> idx, double val) {
            m.at(idx.first, idx.second) = val;
        })
        .def("__eq__", [](const LinearMatrix &a, const LinearMatrix &b) {
            return a.row_count() == b.row_count() && a.col_count() == b.col_count() && std::equal(a.buffer(), a.buffer() + a.total_size(), b.buffer());
        });
}
