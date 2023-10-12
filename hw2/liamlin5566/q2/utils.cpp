#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cmath>


double calc_angle(double x1, double y1, double x2, double y2){
    
    double dot = x1*x2 + y1*y2;
    double n1 = sqrt(x1*x1 + y1*y1);
    double n2 = sqrt(x2*x2 + y2*y2);
    if(n1 == 0 || n2 == 0)  return -100.0; // the range of acos is [-1, 1]
    double cosin = dot / (n1 * n2);
   
    return acos(cosin);
}

PYBIND11_MODULE(_vector, m) {
    m.def("calc_angle_in_python", &calc_angle, "Calculate angle in 2 vector");
}