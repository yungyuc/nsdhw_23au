# include <pybind11/pybind11.h>

#include <iostream>
#include <cmath>


class Vector2D {
private:
    double m_X;
    double m_Y;

public:
    Vector2D(double x, double y) : m_X(x), m_Y(y) {}

    double getX() const { return m_X; }
    double getY() const { return m_Y; }
};


double angle(const Vector2D& vector1, const Vector2D& vector2) {
    double dotProduct = vector1.getX() * vector2.getX() + vector1.getY() * vector2.getY();
    double magnitude1 = sqrt(vector1.getX() * vector1.getX() + vector1.getY() * vector1.getY());
    double magnitude2 = sqrt(vector2.getX() * vector2.getX() + vector2.getY() * vector2.getY());
    
    double cosineTheta = dotProduct / (magnitude1 * magnitude2);
    double radians = acos(cosineTheta);
    
    // Convert radians to degrees
    double degrees = radians * 180.0 / M_PI;
    
    return degrees;
}

namespace py = pybind11;

PYBIND11_MODULE(_vector, m) {
    m.def("angle", &angle, "Calculate the angle between two vectors");
    py::class_<Vector2D>(m, "Vector2D")
        .def(py::init<double, double>(), py::arg("x"), py::arg("y"))
        .def("getX", &Vector2D::getX)
        .def("getY", &Vector2D::getY);
}