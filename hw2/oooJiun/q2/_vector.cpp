#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <utility>
#include <numeric>

double angle(std::pair<double, double> p1, std::pair<double, double> p2){
    double innerProd = p1.first * p2.first + p1.second * p2.second;
    double length = sqrt(pow(p1.first,2) + pow(p1.second,2)) * sqrt(pow(p2.first,2) + pow(p2.second,2));
    double ans = acos(innerProd/length);
    return ans;
}

PYBIND11_MODULE(_vector, m){
    m.doc() = "pybind11 module example";
    m.def("angle", &angle, "Calculates the angle between two vectors in the 2-dimensional Cartesian coordinate system.");
} 