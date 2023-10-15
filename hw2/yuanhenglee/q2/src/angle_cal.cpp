#include "angle_cal.h"
#include <cmath>

double AngleCalculator::calculateAngle(double x1, double y1, double x2, double y2) {
    double dot = x1 * x2 + y1 * y2;
    double len1 = std::sqrt(x1 * x1 + y1 * y1);
    double len2 = std::sqrt(x2 * x2 + y2 * y2);
    double angle = std::acos(dot / (len1 * len2));
    return angle;
}