#include <pybind11/pybind11.h>
#include <math.h>

namespace py = pybind11;

double calculate(double ix, double iy, double jx, double jy)
{
    double i_length = sqrt(ix * ix + iy * iy);
    double j_length = sqrt(jx * jx + jy * jy);
    if (i_length == 0 || j_length == 0)
        throw std::invalid_argument("The length of the vector cannot be zero.");

    double dot_product = ix * jx + iy * jy;
    double determinant = ix * jy - iy * jx;
    return atan2(determinant, dot_product);
}

PYBIND11_MODULE(_vector, m)
{
    m.doc() = "ShangHungWan's hw2 q2 plugin, a function which calculates the angle between two vectors";

    m.def("calculate", &calculate, "A function which calculates the angle between two vectors");
}