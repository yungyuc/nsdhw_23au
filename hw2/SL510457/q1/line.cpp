#include "line.hpp"

Line::Line(size_t size) : x_cords(size), y_cords(size) {}

size_t Line::size() const {
    return x_cords.size();
}

float const & Line::x(size_t it) const {
    return x_cords[it];
}

float & Line::x(size_t it) {
    return x_cords[it];
}

float const & Line::y(size_t it) const {
    return y_cords[it];
}

float & Line::y(size_t it) {
    return y_cords[it];
}