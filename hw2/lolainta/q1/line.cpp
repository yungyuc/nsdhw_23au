#include "line.hpp"

Line::Line(size_t size) : _points(size) {}

size_t Line::size() const
{
    return _points.size();
}

float const &Line::x(size_t it) const
{
    return _points[it].first;
}

float &Line::x(size_t it)
{
    return _points[it].first;
}

float const &Line::y(size_t it) const
{
    return _points[it].second;
}

float &Line::y(size_t it)
{
    return _points[it].second;
}