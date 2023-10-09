#include <cstddef>
#include <vector>
#include "Line.h"

Line::Line() {
    this->m_x.clear();
    this->m_y.clear();
} 

Line::Line(Line const& target) {
    this->m_x.clear();
    this->m_y.clear();

    m_size = target.size();
    this->m_x.resize(m_size);
    this->m_y.resize(m_size);
    
    for (size_t i = 0; i < m_size; i++) {
        float cur_x = target.x(i);
        float cur_y = target.y(i);
        this->m_x[i] = cur_x;
        this->m_y[i] = cur_y;
    }
}

Line::Line(size_t size) {
    this->m_size = size;
    this->m_x.clear();
    this->m_x.resize(m_size);
    this->m_y.clear();
    this->m_y.resize(m_size);
}

Line::~Line(){
    this->m_size = 0;
    this->m_x.clear();
    this->m_y.clear();
}

size_t Line::size() const {
    return m_size;
}

float const & Line::x(size_t it) const {
  return this->m_x[it];
}

float & Line::x(size_t it) {
    return this->m_x[it];
}

float const & Line::y(size_t it) const {
    return this->m_y[it];
}

float & Line::y(size_t it) {
    return this->m_y[it];
}
