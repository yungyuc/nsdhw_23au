#include <pybind11/pybind11.h>
#include "matrix.h"
#include "allocator.h"

namespace py = pybind11;

PYBIND11_MODULE(_matrix, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<int, int>())
        .def("__getitem__", [](const Matrix &m, std::pair<int, int> i) { return m(i.first, i.second); })
        .def("__setitem__", [](Matrix &m, std::pair<int, int> i, double v) { m(i.first, i.second) = v; })
        .def("__eq__", &Matrix::operator==)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol);
    m.def("multiply_naive", &multiply_naive, "Multiply two matrices using naive algorithm");
    m.def("multiply_tile", &multiply_tile, "Multiply two matrices using tiling",
        py::arg("mat1"), py::arg("mat2"), py::arg("tile_size") = 32
    );
    m.def("multiply_mkl", &multiply_mkl, "Multiply two matrices using MKL");
    m.def("bytes", &Allocator<double>::bytes);
    m.def("allocated", &Allocator<double>::allocated);
    m.def("deallocated", &Allocator<double>::deallocated);       
}