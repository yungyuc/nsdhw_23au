#include"_matrix.hpp"

#include<stdexcept>

#include<pybind11/pybind11.h>
#include<pybind11/operators.h>
#include<pybind11/stl.h>

#include<mkl/mkl.h>

#include"matrix.hpp"


void validate_multiply(const Matrix& mat1, const Matrix& mat2)
{
    if(mat1.ncol() != mat2.nrow())
    {
        throw std::out_of_range(
            "the number of first matrix column "
            "differs from that of second matrix row");
    }
}

Matrix multiply_naive(const Matrix& mat1, const Matrix& mat2)
{
    validate_multiply(mat1, mat2);

    Matrix ret(mat1.nrow(), mat2.ncol());

    const std::size_t nrow1 = mat1.nrow();
    const std::size_t ncol1 = mat1.ncol();
    const std::size_t ncol2 = mat2.ncol();

    for(std::size_t i = 0; i < nrow1; ++i)
    {
        for(std::size_t k = 0; k < ncol2; ++k)
        {
            for(std::size_t j = 0; j < ncol1; ++j)
            {
                ret(i, j) += mat1(i, k) * mat2(k, j);
            }
        }
    }

    return ret;
}

Matrix multiply_tile(
    const Matrix& mat1, const Matrix& mat2, std::size_t tile_size)
{
    validate_multiply(mat1, mat2);

    Matrix ret(mat1.nrow(), mat2.ncol());

    const std::size_t nrow1 = mat1.nrow();
    const std::size_t ncol1 = mat1.ncol();
    const std::size_t ncol2 = mat2.ncol();

    // TODO
    for(std::size_t i = 0; i < nrow1; i += tile_size)
    {
        for(std::size_t j = 0; j < ncol2; j += tile_size)
        {
            for(std::size_t k = 0; k < ncol1; k += tile_size)
            {
                for(std::size_t ii = i; ii < std::min(i + tile_size, nrow1); ii++)
                {
                    for(std::size_t jj = j; jj < std::min(j + tile_size, ncol2); jj++)
                    {
                        for(std::size_t kk = k; kk < std::min(k + tile_size, ncol1); kk++)
                        {
                            ret(ii, jj) += mat1(ii, kk) * mat2(kk, jj);
                        }
                    }
                }
            }
        }
    }

    return ret;
}

Matrix multiply_mkl(const Matrix& mat1, const Matrix& mat2)
{
    validate_multiply(mat1, mat2);

    Matrix ret(mat1.nrow(), mat2.ncol());

    cblas_dgemm(
        CblasRowMajor,
        CblasNoTrans, CblasNoTrans,
        mat1.nrow(), mat1.ncol(), mat2.ncol(),
        1,
        mat1.buffer(), mat1.ncol(),
        mat2.buffer(), mat2.ncol(),
        0,
        ret.buffer(), ret.ncol()
    );

    return ret;
}


PYBIND11_MODULE(_matrix, m)
{
    using namespace pybind11::literals;

    m.doc() = "A simple library about matrix tiling";

    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<std::size_t, std::size_t>(), "nrow"_a, "ncol"_a)
        .def_property_readonly("nrow", &Matrix::nrow)
        .def_property_readonly("ncol", &Matrix::ncol)
        .def(pybind11::self == pybind11::self)  // "__eq__"
        // .def("__eq__", &Matrix::operator==)
        .def("__setitem__",
            [](Matrix& self, std::array<std::size_t, 2> idx, double val)
            {
                self(idx.at(0), idx.at(1)) = val;
            }
        )
        .def("__getitem__",
            [](const Matrix& self, std::array<std::size_t, 2> idx)
            {
                return self(idx.at(0), idx.at(1));
            }
        );

    m.def("multiply_naive", &multiply_naive, "mat1"_a, "mat2"_a);
    m.def("multiply_tile", &multiply_tile, "mat1"_a, "mat2"_a, "tile_size"_a);
    m.def("multiply_mkl", &multiply_mkl, "mat1"_a, "mat2"_a);
}
