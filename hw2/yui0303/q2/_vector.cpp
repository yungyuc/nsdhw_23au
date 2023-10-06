#include <iostream>
// #include <vector>
#include <cmath>
#include <utility>
#include <pybind11/pybind11.h>

namespace py = pybind11;

double vector_length(std::pair<double, double> vec)
{
    return sqrt(vec.first*vec.first + vec.second*vec.second);
}

double cal_angle(std::pair<double, double> v1, std::pair<double, double> v2)
{
    double dot_product  = v1.first*v2.first + v1.second*v2.second;
    double len = vector_length(v1)*vector_length(v2);
    
    if(len == 0) return -1; // invalid

    return acos(dot_product/len);
}

PYBIND11_MODULE(_vector, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring
    m.def("cal_angle", &cal_angle, "A function that calculate the angle between two vectors");
}