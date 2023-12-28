#include <cstddef>
#include <mkl.h>
#include <stdexcept>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <iomanip>
#include <iostream>
namespace py = pybind11;

class Matrix {
public:
    Matrix(size_t nrow, size_t ncol)
        : _nrow(nrow), _ncol(ncol) {
        _reset_buffer(nrow, ncol);
    }
#ifndef PYBIND
    Matrix(size_t nrow, size_t ncol, std::vector<double> const& vec)
        : _nrow(nrow), _ncol(ncol) {
        _reset_buffer(nrow, ncol);
        (*this) = vec;
    }
    Matrix& operator=(std::vector<double> const& vec) {
        if (size() != vec.size()) {
            throw std::out_of_range("Out");
        }

        size_t k = 0;
        for (size_t i = 0; i < _nrow; i++) {
            for (size_t j = 0; j < _ncol; j++) {
                (*this)(i, j) = vec[k];
                k++;
            }
        }
        return *this;
    }
#endif
    double& operator[](std::pair<size_t, size_t> idx) const {
        if (idx.first > _nrow || idx.second > _ncol) {
            throw std::out_of_range("Out");
        }
        return _buffer[_index(idx.first, idx.second)];
    }

    double operator()(size_t row, size_t col) const {
        if (row > _nrow || col > _ncol) {
            throw std::out_of_range("Out");
        }
        return _buffer[_index(row, col)];
    }
    double& operator()(size_t row, size_t col) {
        if (row > _nrow || col > _ncol) {
            throw std::out_of_range("Out");
        }
        return _buffer[_index(row, col)];
    }

    bool operator==(Matrix& other) const {
        if (other.nrow() != _nrow && other.ncol() != _ncol) {
            throw std::length_error("row != nrow or col != ncol");
        }
        for (size_t i = 0; i < _nrow; i++) {
            for (size_t j = 0; j < _ncol; j++) {
                if (_buffer[_index(i, j)] != other(i, j))
                    return false;
            }
        }
        return true;
    }

    size_t nrow() const {
        return _nrow;
    }

    size_t ncol() const {
        return _ncol;
    }

    size_t size() const {
        return _nrow * _ncol;
    }

    double* get_buffer() const {
        return _buffer;
    }

    void _reset_buffer(size_t nrow, size_t ncol) {
        if (_buffer)
            delete[] _buffer;
        const size_t nelement = nrow * ncol;
        if (nelement)
            _buffer = new double[nelement];
        else
            _buffer = nullptr;
        _nrow = nrow;
        _ncol = ncol;
    }

    size_t _index(size_t row, size_t col) const {
        return row * _ncol + col;
    }
    py::array_t<double> array() {
        return py::array_t<double>(
            { nrow(), ncol() }, // shape
            { sizeof(double) * ncol(), sizeof(double) }, // C-style contiguous strides for ncol doubles
            _buffer, // the data pointer
            py::cast(this) // let handle object reference *this*
        );
    }
    size_t _nrow = 0, _ncol = 0;
    double* _buffer = nullptr;
};

Matrix multiply_naive(Matrix const& mat1, Matrix const& mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range("mat1.col != mat2.row");
    }
    Matrix ret(mat1.nrow(), mat2.ncol());
    for (size_t i = 0; i < ret.nrow(); i++) {
        for (size_t k = 0; k < ret.ncol(); k++) {
            for (size_t j = 0; j < mat1.ncol(); j++) {
                ret(i, k) += mat1(i, j) * mat2(j, k);
            }
        }
    }
    return ret;
}
Matrix multiply_tile(Matrix& mat1, Matrix& mat2, size_t tsize) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range("the number of first matrix column differs from that of second matrix row");
    }
    Matrix ret(mat1.nrow(), mat2.ncol());

    for (size_t row = 0; row < mat1.nrow(); row += tsize)
        for (size_t col = 0; col < mat2.ncol(); col += tsize)
            for (size_t inner = 0; inner < mat1.ncol(); inner += tsize)
                for (size_t i = row; i < std::min(mat1.nrow(), row + tsize); i++)
                    for (size_t j = col; j < std::min(mat2.ncol(), col + tsize); j++)
                        for (size_t k = inner; k < std::min(mat1.ncol(), inner + tsize); k++)
                            ret(i, j) += mat1(i, k) * mat2(k, j);
    return ret;
}

Matrix multiply_mkl(Matrix const& mat1, Matrix const& mat2) {
    if (mat1.ncol() != mat2.nrow()) {
        throw std::out_of_range("mat1.col != mat2.row");
    }
    Matrix ret(mat1.nrow(), mat2.ncol());
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                mat1.nrow(), mat2.ncol(), mat1.ncol(), 1.0, mat1._buffer, mat1.ncol(),
                mat2._buffer, mat2.ncol(), 0.0, ret._buffer, ret.ncol());
    return ret;
}

#ifndef PYBIND
std::ostream& operator<<(std::ostream& ostr, Matrix const& mat) {
    for (size_t i = 0; i < mat.nrow(); i++) {
        ostr << std::endl
             << " ";
        for (size_t j = 0; j < mat.ncol(); j++) {
            ostr << " " << std::setw(2) << mat(i, j);
        }
    }
    return ostr;
}

int main() {
    Matrix mat1(2, 3, std::vector<double>{ 1, 2, 3, 4, 5, 6 });
    Matrix mat2(3, 2, std::vector<double>{ 1, 2, 3, 4, 5, 6 });
    std::cout << "Naive : " << std::endl;
    Matrix mat3 = multiply_naive(mat1, mat2);

    std::cout << mat1 << std::endl;
    std::cout << mat2 << std::endl;
    std::cout << mat3 << std::endl;

    std::cout << "MKL : " << std::endl;
    mat3 = multiply_mkl(mat1, mat2);

    std::cout << mat1 << std::endl;
    std::cout << mat2 << std::endl;
    std::cout << mat3 << std::endl;

    std::cout << "Tile : " << std::endl;
    mat3 = multiply_tile(mat1, mat2, 2);

    std::cout << mat1 << std::endl;
    std::cout << mat2 << std::endl;
    std::cout << mat3 << std::endl;
}
#else
PYBIND11_MODULE(_matrix, m) {
    pybind11::class_<Matrix>(m, "Matrix").def(pybind11::init<size_t, size_t>()).def("__setitem__", [](Matrix& self, std::pair<size_t, size_t> idx, double num) { self(idx.first, idx.second) = num; }).def("__getitem__", &Matrix::operator[]).def("__eq__", &Matrix::operator==).def_property_readonly("nrow", &Matrix::nrow).def_property_readonly("ncol", &Matrix::ncol).def_property("array", &Matrix::array, nullptr);
    m.def("multiply_naive", &multiply_naive);
    m.def("multiply_tile", &multiply_tile);
    m.def("multiply_mkl", &multiply_mkl);
}
#endif