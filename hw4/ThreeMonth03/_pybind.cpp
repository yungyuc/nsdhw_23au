#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include "_matrix.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_matrix, m) {
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
	    .def(py::init<Matrix const&>())
	    .def("__getitem__", [](Matrix &mat, std::pair<size_t, size_t> index){
	        return mat(index.first, index.second);
	    })
	    .def("__setitem__", [](Matrix &mat, std::pair<size_t, size_t> index, double val){
	    	mat(index.first, index.second) = val;
	    })
        .def("__eq__", &Matrix::operator==)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_mkl", &multiply_mkl);
    m.def("bytes", &bytes);
    m.def("allocated", &allocated);
    m.def("deallocated", &deallocated);
}