#include "Line.hpp"

Line::Line(): m_buffer_size(0){
    m_x_buffer.resize(0);
    m_y_buffer.resize(0);
}

Line::Line(Line const & line):  m_buffer_size(line.m_buffer_size),
                                m_x_buffer(line.m_x_buffer),
                                m_y_buffer(line.m_y_buffer){
}

Line::Line(Line && line){
    m_buffer_size = std::move(line.m_buffer_size);
    m_x_buffer = std::move(line.m_x_buffer);
    m_y_buffer = std::move(line.m_y_buffer);
}

Line & Line::operator=(Line const & line){
    if(this != &line){
        m_buffer_size = line.m_buffer_size;
        m_x_buffer = line.m_x_buffer;
        m_y_buffer = line.m_y_buffer;
    }
    return *this;
}

Line & Line::operator=(Line && line){
    if(this != &line){
        m_buffer_size = std::move(line.m_buffer_size);
        m_x_buffer = std::move(line.m_x_buffer);
        m_y_buffer = std::move(line.m_y_buffer);
    }
    return *this;
}

Line::Line(std::size_t size): m_buffer_size(size){
    m_x_buffer.resize(size);
    m_y_buffer.resize(size);
}

std::size_t Line::size() const{
    return m_buffer_size;
}

float const & Line::x(std::size_t it) const{
    return m_x_buffer[it];
}

float & Line::x(std::size_t it){
    return m_x_buffer[it];
}
float const & Line::y(std::size_t it) const{
    return m_y_buffer[it];
}
float & Line::y(std::size_t it){
    return m_y_buffer[it];
}