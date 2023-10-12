#include "line.hpp"

// #include <algorithm>
// #include <iterator>
// #include <vector>

// Default constructor
Line::Line() = default;

// Copy constructor
Line::Line(Line const &line) = default;

// Move constructor
Line::Line(Line &&) = default;

// Copy assignment operator
Line &Line::operator=(Line const &) = default;

// Move assignment operator
Line &Line::operator=(Line &&) = default;

// Desturctor
Line::~Line() = default;

Line::Line(size_t size) {
    this->m_x.resize(size);
    this->m_y.resize(size);
}

size_t Line::size() const {
    return this->m_x.size();
}

// getter
float const &Line::x(size_t it) const {
    return this->m_x[it];
}

// setter
float &Line::x(size_t it) {
    return this->m_x[it];
}

// getter
float const &Line::y(size_t it) const {
    return this->m_y[it];
}

// setter
float &Line::y(size_t it) {
    return this->m_y[it];
}
