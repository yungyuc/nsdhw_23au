#include <pybind11/pybind11.h>
#include "angle_cal.h"

namespace py = pybind11;

PYBIND11_MODULE(angle_cal, m) {
    m.def("calculateAngle", &AngleCalculator::calculateAngle, "A function which calculates the angle between two vectors");
}