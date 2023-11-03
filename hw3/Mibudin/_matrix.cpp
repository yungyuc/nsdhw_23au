#include"_matrix.hpp"

#include<algorithm>

#include<pybind11/pybind11.h>
#include<pybind11/operators.h>


Matrix::Matrix(std::size_t nrow, std::size_t ncol)
    : m_nrow(nrow), m_ncol(ncol), m_buffer(new double[nrow * ncol]{}) {};

bool Matrix::operator==(const Matrix& rhs) const
{
    if(m_nrow != rhs.m_nrow || m_ncol != rhs.m_ncol)
    {
        return false;
    }

    return std::equal(m_buffer, m_buffer + m_nrow * m_ncol, rhs.m_buffer);
}


PYBIND11_MODULE(_matrix, m)
{
    m.doc() = "A simple library about matrix tiling";

    using namespace pybind11::literals;

    pybind11::class_<Matrix>(m, "Matrix")
        .def(pybind11::init<std::size_t, std::size_t>())
        .def(pybind11::self == pybind11::self);  // "__eq__"
    
}
