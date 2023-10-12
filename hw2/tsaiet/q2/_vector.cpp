#include <iostream>
#include <cmath>
#include <pybind11/pybind11.h>

double get_angle(float x1, float y1, float x2, float y2){
	if((x1==x2) && (y1==y2)) return 0;
	double a = sqrt(pow(x1,2) + pow(y1,2));
	double b = sqrt(pow(x2,2) + pow(y2,2));
	double c = sqrt(pow(x1-x2,2) + pow(y1-y2,2));
	double numerator = pow(a,2) + pow(b,2) - pow(c,2);
	double denominator = 2 * a * b;
	return acos(numerator/denominator);
}

PYBIND11_MODULE(_vector, m){
	m.doc() = "calculates the angle between two vectors in the 2D Cartesian coordinate system";
	m.def("get_angle_py", &get_angle, "calculates the angle between two vectors in the 2D Cartesian coordinate system",pybind11::arg("x1"), pybind11::arg("y1"), pybind11::arg("x2"), pybind11::arg("y2"));
}

