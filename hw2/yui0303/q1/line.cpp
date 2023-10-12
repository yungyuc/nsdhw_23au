#include "line.hpp"

Line::Line(Line const & other) //copy constructor
{
    if(other.points.empty()){ // the object is empty
        if(!points.empty()){
            points.clear();
            std::vector<std::pair<float, float>>().swap(points); // clear did not free the memory space of vector actually
        }
    }
    else{
        points = other.points;
    }
}

Line::Line(Line && other) // move constructor
{
    points.swap(other.points);
}

Line & Line::operator=(Line const & other) //copy assignment operator
{
    if (this == &other) { return *this;}

    if(!other.points.empty()){
        if(points.empty()) { points.clear(); }
        points = other.points;
    }
    else{
        if(!points.empty()){
            points.clear();
            std::vector<std::pair<float, float>>().swap(points);
        }
    }
    return *this;
}

Line & Line::operator=(Line && other){
    if(this == &other) { return *this; }
    points.swap(other.points);
    return *this;
}

Line::Line(size_t size) { points.resize(size); }

size_t Line::size() const { return points.size(); }

float const & Line::x(size_t it) const { return points[it].first; } //getter
float & Line::x(size_t it) { return points[it].first; } //setter
float const & Line::y(size_t it) const { return points[it].second; } //getter
float & Line::y(size_t it) { return points[it].second; } //setter


Line::~Line() { points.clear(); std::vector<std::pair<float, float>>().swap(points); }

