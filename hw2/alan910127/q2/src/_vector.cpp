#include <pybind11/pybind11.h>

#include <cmath>
#include <utility>

namespace py = pybind11;

using Vector2D = std::pair<double, double>;

double calculate_angle(const Vector2D& v1, const Vector2D& v2) {
    auto [x1, y1] = v1;
    auto [x2, y2] = v2;

    double dot = x1 * x2 + y1 * y2;
    double len1 = std::sqrt(x1 * x1 + y1 * y1);
    double len2 = std::sqrt(x2 * x2 + y2 * y2);
    return std::acos(dot / (len1 * len2));
}

PYBIND11_MODULE(_vector, m) {
    m.doc() = "A module for vector calculation";

    m.def("calculate_angle", &calculate_angle, py::arg("v1"), py::arg("v2"),
          "A function to calculate angle between two vectors in radian");
}