#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "CustomAllocator.hpp"
#include "Matrix.hpp"
#include "multiply.hpp"

namespace py = pybind11;

void bind_Matrix(py::module &m) {
  py::class_<Matrix>(m, "Matrix", pybind11::buffer_protocol())
      .def(py::init<int, int>())
      .def_property_readonly("nrow", &Matrix::get_rows)
      .def_property_readonly("ncol", &Matrix::get_cols)
      .def("__setitem__",
           [](Matrix &mat, std::pair<size_t, size_t> idx, double value) {
             auto [u, v] = idx;
             mat(u, v) = value;
           })
      .def("__getitem__",
           [](Matrix &mat, std::pair<size_t, size_t> idx) {
             auto [u, v] = idx;
             return mat(u, v);
           })
      .def("__eq__", [](const Matrix &A, const Matrix &B) { return A == B; })
      .def_property(
          "array",
          [](Matrix &m) -> py::array_t<double> {
            return py::array_t<double>(
                {m.get_rows(), m.get_cols()},
                {sizeof(double) * m.get_cols(), sizeof(double)}, m.get_data(),
                py::cast(m));
          },
          nullptr);
}

void bind_multiply(py::module &m) {
  m.def("multiply_naive", &MatrixMultiply::multiply_naive);
  m.def("multiply_tile", &MatrixMultiply::multiply_tile);
  m.def("multiply_mkl", &MatrixMultiply::multiply_mkl);
}

void bind_CustomAllocator(py::module &m) {
  m.def("bytes", &CustomAllocator<double>::bytes);
  m.def("allocated", &CustomAllocator<double>::allocated);
  m.def("deallocated", &CustomAllocator<double>::deallocated);
}

PYBIND11_MODULE(_matrix, m) {
  m.doc() = "pybind11 _matix package";
  bind_Matrix(m);
  bind_multiply(m);
  bind_CustomAllocator(m);
}
