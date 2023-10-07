#include<cmath>
#include<array>
#include<limits>
#include<numeric>

#include<pybind11/pybind11.h>
#include<pybind11/stl.h>


/**
 * @brief Calculate the angle (in radians) between two vectors in the 
 *        2-dimensional Cartesian coordinate system
 * 
 * @param vec1 the first 2D vector (double)
 * @param vec2 the second 2D vector (douoble)
 * @return double the angle in radians between the given two vectors
 */
double rad_between_vec2d(
    const std::array<double, 2> vec1, const std::array<double, 2> vec2)
{
    const double x1 = vec1.at(0), y1 = vec1.at(1);
    const double x2 = vec2.at(0), y2 = vec2.at(1);

    if((x1 == 0 && y1 == 0) || (x2 == 0 && y2 == 0))
    {
        // Some of input vector are zero-length.
        return std::numeric_limits<double>::quiet_NaN();
    }

    double det = x1 * y2 - y1 * x2;
    double dot = x1 * x2 + y1 * y2;

    double angle = abs(atan2(det, dot));

    return angle;
}


PYBIND11_MODULE(_vector, m)
{
    m.doc() = "A simple library about computing angles and vectors";

    using namespace pybind11::literals;
    m.def("rad_between_vec2d", &rad_between_vec2d,
        "Calculate the angle (in radians) between two vectors in the "
        "2-dimensional Cartesian coordinate system",
        "vec1"_a, "vec2"_a
    );
}
