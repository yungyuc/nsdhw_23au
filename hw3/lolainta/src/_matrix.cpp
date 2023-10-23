#include <pybind11/pybind11.h>

#include "Matrix.hpp"
namespace py = pybind11;

PYBIND11_MODULE(_matrix, m) {
  m.doc() = "pybind11 _matix package";  // optional module docstring
  py::class_<Matrix>(m, "Matrix")
      .def(py::init<int, int>())
      .def_property_readonly("rows", &Matrix::get_rows)
      .def_property_readonly("cols", &Matrix::get_cols)
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