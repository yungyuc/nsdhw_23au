
#include <pybind11/pybind11.h>

#include "Matrix.hpp"
#include "multiply.hpp"
namespace py = pybind11;

void bind_Matrix(py::module &m) {
  py::class_<Matrix>(m, "Matrix")
      .def(py::init<int, int>())
      .def_property_readonly("nrow", &Matrix::get_rows)
      .def_property_readonly("ncol", &Matrix::get_cols)
      .def("__setitem__",
           [](Matrix &mat, std::pair<size_t, size_t> idx, double value) {
             auto [u, v] = idx;
             mat(u, v) = value;
           })
      .def("__getitem__", [](Matrix &mat, std::pair<size_t, size_t> idx) {
        auto [u, v] = idx;
        return mat(u, v);
      });
}

void bind_multiply(py::module &m) {
  m.def("multiply_naive", &multiply_naive);
  m.def("multiply_tile", &multiply_tile);
  m.def("multiply_mkl", &multiply_mkl);
}

PYBIND11_MODULE(_matrix, m) {
  m.doc() = "pybind11 _matix package";
  bind_Matrix(m);
  bind_multiply(m);
}