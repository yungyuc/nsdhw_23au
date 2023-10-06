#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <utility>
#include <numeric>

double angle_cal(std::pair<double, double> p1, std::pair<double, double> p2){
    double inn_prod = p1.first * p2.first + p1.second * p2.second;
    double length = sqrt(pow(p1.first,2) + pow(p1.second,2)) * sqrt(pow(p2.first,2) + pow(p2.second,2));
    return acos(inn_prod / length);
}

PYBIND11_MODULE(angle_calculation, m){
    m.doc() = "pybind11 module example";
    m.def("angle_py", &angle_cal, "A Program that calculates the angle (in radians) between two vectors in the 2-dimensional Cartesian coordinate system");
}