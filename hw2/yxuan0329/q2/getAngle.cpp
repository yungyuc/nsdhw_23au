#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cmath>

using namespace std;
namespace py = pybind11;

double getAngle(const vector<double>& v1, const vector<double>& v2){
    if (v1.size() != 2 || v2.size() != 2) {
	throw std::invalid_argument("Invalid. Vector should be 2-dimensional.");
    }
    double p1, p2;
    p1 = sqrt(v1[0] * v1[0] + v1[1] * v1[1]);
    p2 = sqrt(v2[0] * v2[0] + v2[1] * v2[1]);
    return acos((v1[0] * v2[0] + v1[1] * v2[1]) / (p1 * p2));
}

PYBIND11_MODULE(_vector, m){
    m.doc() = "getAngle function";
    m.def("getAngle", &getAngle, "A function return radian of two 2d vectors");
}
