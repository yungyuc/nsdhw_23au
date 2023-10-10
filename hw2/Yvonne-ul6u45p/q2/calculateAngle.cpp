#include <iostream>
#include <vector>
#include <math.h>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
using namespace std;

float calculateAngle(const vector<float> &v1, const vector<float> &v2) {
    if (v1.size() != 2 || v2.size() != 2)
	    throw invalid_argument("Input vector should be 2-dimensional.");

    float dot_product = v1[0]*v2[0] + v1[1]*v2[1];
    float length = sqrt(v1[0]*v1[0] + v1[1]*v1[1]) * sqrt(v2[0]*v2[0] + v2[1]*v2[1]);
    if (length == 0)
        throw domain_error("Length of Input vector cannot be zero!");
    
    float angle_rad = acos(dot_product/length);
    
    return angle_rad;
}

// for Check
int main() {
    vector<float> v1 = {1, 1};
    vector<float> v2 = {2, 2};
    float angle_rad = calculateAngle(v1, v2);
    cout << angle_rad << endl;

    if (angle_rad == 0)
        cout << "Is 0." << endl;
    
    return 0;
}

PYBIND11_MODULE(_vector, m) {   // module name
    m.doc() = "Calculates the angle (in radians) between two vectors in the 2-dimensional Cartesian coordinate system.";
    m.def("calculateAngle", &calculateAngle, pybind11::arg("v1"), pybind11::arg("v2"));
}