#include "line.hpp"

Line::Line(size_t size) : cord(size){}

size_t Line::size() const{
    return cord.size();
}

float const &Line::x(size_t it) const{
    return cord[it].first;
}

float &Line::x(size_t it){
    return cord[it].first;
}

float const &Line::y(size_t it) const{
    return cord[it].second;
}

float &Line::y(size_t it){
    return cord[it].second;
}