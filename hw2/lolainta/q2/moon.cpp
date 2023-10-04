#include <pybind11/pybind11.h>
#include <numeric>
namespace py = pybind11;

double magic(std::vector<double> p1, std::vector<double> p2)
{
    return acos(inner_product(p1.begin(), p1.end(), p2.begin(), 0.0) / (sqrt(inner_product(p1.begin(), p1.end(), p1.begin(), 0.0)) * sqrt(inner_product(p2.begin(), p2.end(), p2.begin(), 0.0))));
}

PYBIND11_MODULE(_vector, m)
{
    m.doc() = "pybind11 plugin"; // optional module docstring

    m.def("magic", &magic, "A C++ function that calculates the angle (in radians) between two vectors in the 2-dimensional Cartesian coordinate system.");
}