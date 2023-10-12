// Naming convention reference: https://google.github.io/styleguide/cppguide.html#Naming

#include <pybind11/pybind11.h>

#include <cmath>

double CalculateRadian(double x1, double y1, double x2, double y2) {
    double inner_product = x1 * x2 + y1 * y2;
    double first_length = sqrt(x1 * x1 + y1 * y1);
    double second_length = sqrt(x2 * x2 + y2 * y2);
    if (first_length == 0 || second_length == 0) {
        return NAN;
    } else {
        return abs(acos(inner_product / (first_length * second_length)));
    }
}

PYBIND11_MODULE(_vector, m) {
    m.def("calculate_radian", &CalculateRadian, "A function that calculate the radians of two vectors");
}
