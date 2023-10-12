#include <cmath>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>


double calculate_angle(double x1, double y1, double x2, double y2){
    double n1 = sqrt(x1*x1 + y1*y1);
    double n2 = sqrt(x2*x2 + y2*y2);
    if(!n1 || !n2)  return -2; //Error
    double dot_product = x1*x2 + y1*y2;
    double cosine = dot_product / (n1 * n2);
    return acos(cosine);
}

PYBIND11_MODULE(_vector, m) {
    m.def("calculate_angle_py", &calculate_angle, "Calculate angle of 2D Cartesian coordination system", 
    pybind11::arg("x1"), pybind11::arg("y1"), pybind11::arg("x2"), pybind11::arg("y2"));
}