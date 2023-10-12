#include <iostream>
#include <cmath>
#include <pybind11/pybind11.h>
namespace py = pybind11;
using namespace std;

double AngleBtwVectors(double x1, double y1, double x2, double y2) {
  double dot_product = x1 * x2 + y1 * y2;
  double length1 = sqrt(x1 * x1 + y1 * y1);
  double length2 = sqrt(x2 * x2 + y2 * y2);
  if(length1==0 || length2==0){
    return NAN;
    }
  double cosine = dot_product / (length1 * length2);
  cosine = min(cosine,1.0);
  cosine = max(cosine,-1.0);
  double theta = acos(cosine);
  return theta;
}


PYBIND11_MODULE(_vector, m) {
    m.doc() = "pybind11 example plugin"; 

    m.def("AngleBtwVectors", &AngleBtwVectors, 
            "A function that calculates the angle(in radians) between two \
            vectors in the 2-dimensional Cartesian coordinate system.");
}