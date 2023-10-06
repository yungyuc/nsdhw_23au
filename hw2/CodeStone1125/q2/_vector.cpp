# include <pybind11/pybind11.h>
# include <pybind11/stl.h>
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

// Define a custom exception class for zero-length vectors
class ZeroLengthVectorException : public std::runtime_error {
public:
    ZeroLengthVectorException(const std::string& message) : std::runtime_error(message) {}
};

double angle(const Vector2D& vector1, const Vector2D& vector2) {

    // Check for zero-length vectors
    if (vector1.getX() == 0 && vector1.getY() == 0) {
        throw ZeroLengthVectorException("Vector1 is a zero-length vector");
    }
    if (vector2.getX() == 0 && vector2.getY() == 0) {
        throw ZeroLengthVectorException("Vector2 is a zero-length vector");
    }

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
    
    // Expose the ZeroLengthVectorException class
    py::register_exception<ZeroLengthVectorException>(m, "ZeroLengthVectorException");
    
    py::class_<Vector2D>(m, "Vector2D")
        .def(py::init<double, double>(), py::arg("x"), py::arg("y"))
        .def("getX", &Vector2D::getX)
        .def("getY", &Vector2D::getY);
}