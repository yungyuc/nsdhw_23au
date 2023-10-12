#include "Line.h"

Line::Line() {}

Line::Line(Line const &other)
{
    x_coords = other.x_coords;
    y_coords = other.y_coords;
}

Line::Line(Line &&other)
{
    x_coords = std::move(other.x_coords);
    y_coords = std::move(other.y_coords);
}

Line &Line::operator=(Line const &other)
{
    if (this != &other)
    {
        x_coords = other.x_coords;
        y_coords = other.y_coords;
    }
    return *this;
}

Line &Line::operator=(Line &&other)
{
    if (this != &other)
    {
        x_coords = std::move(other.x_coords);
        y_coords = std::move(other.y_coords);
    }
    return *this;
}

Line::Line(size_t size)
{
    x_coords.resize(size);
    y_coords.resize(size);
}

Line::~Line() {}

size_t Line::size() const
{
    return x_coords.size();
}

float const &Line::x(size_t it) const
{
    return x_coords[it];
}

float &Line::x(size_t it)
{
    return x_coords[it];
}

float const &Line::y(size_t it) const
{
    return y_coords[it];
}

float &Line::y(size_t it)
{
    return y_coords[it];
}
