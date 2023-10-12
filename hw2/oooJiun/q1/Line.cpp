#include "Line.hpp"
#include <iostream>

Line::Line(){}

Line::Line(Line const & line){
    this->vector_x = line.vector_x;
    this->vector_y = line.vector_y;
}

Line::Line(Line && line){
    this->vector_x = line.vector_x;
    this->vector_y = line.vector_y;
}

Line & Line::operator = (Line const & line){
    vector_x = line.vector_x;
    vector_y = line.vector_y;
    return *this;
}

Line & Line::operator = (Line && line){
    vector_x = line.vector_x;
    vector_y = line.vector_y;
    return *this;
}

Line::Line(size_t size){
    this->vector_x.assign(size, 0);
    this->vector_y.assign(size, 0);
}

Line::~Line(){
    this->vector_x.clear();
    this->vector_y.clear();
}

size_t Line::size() const{
    return this->vector_x.size();
}

const float & Line::x(size_t it) const{
    return this->vector_x.at(it);
}

float & Line::x(size_t it){
    return this->vector_x.at(it);
}

const float & Line::y(size_t it) const{
    return this->vector_y.at(it);
}

float & Line::y(size_t it){
    return this->vector_y.at(it);
}

int main(int, char **)
{
    Line line(3);
    line.x(0) = 0; line.y(0) = 1;
    line.x(1) = 1; line.y(1) = 3;
    line.x(2) = 2; line.y(2) = 5;

    Line line2(line);
    line2.x(0) = 9;

    std::cout << "line: number of points = " << line.size() << std::endl;
    for (size_t it=0; it<line.size(); ++it)
    {
        std::cout << "point " << it << ":"
                << " x = " << line.x(it)
                << " y = " << line.y(it) << std::endl;
    }

    std::cout << "line2: number of points = " << line.size() << std::endl;
    for (size_t it=0; it<line.size(); ++it)
    {
        std::cout << "point " << it << ":"
                << " x = " << line2.x(it)
                << " y = " << line2.y(it) << std::endl;
    }

    return 0;
} 