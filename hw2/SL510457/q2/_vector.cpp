#include <cmath>
#include <pybind11/pybind11.h>

double calculate_angle(std::pair<double, double> v1, std::pair<double, double> v2) {
    double dot_product = v1.first*v2.first + v1.second*v2.second;
    double magnitude_product = std::sqrt(v1.first*v1.first + v1.second*v1.second) * std::sqrt(v2.first*v2.first + v2.second*v2.second);
    return std::acos(dot_product / magnitude_product);
}

PYBIND11_MODULE(_vector, m) {
    m.doc() = "pybind11 module example";
    m.def("calculate_angle", &calculate_angle, "A function which calculates angle between two vectors");
}