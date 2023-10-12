#include <pybind11/pybind11.h>
#include <cmath>

double calculate_angle(double x1, double y1, double x2, double y2) {
    // Calculate the dot product of the two vectors
    double dot_product = x1 * x2 + y1 * y2;

    // Calculate the magnitudes of the vectors
    double magnitude1 = sqrt(x1 * x1 + y1 * y1);
    double magnitude2 = sqrt(x2 * x2 + y2 * y2);

    // Calculate the angle in radians using the dot product
    double angle = acos(dot_product / (magnitude1 * magnitude2));
    
    return angle;
}


namespace py = pybind11;

PYBIND11_MODULE(_vector, m) {
    m.def("calculate_angle", &calculate_angle, "Calculate the angle between two vectors");
}
