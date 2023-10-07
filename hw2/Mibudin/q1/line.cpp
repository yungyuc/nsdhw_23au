#include"line.hpp"

Line::Line(size_t size)
    : m_coord(std::vector<std::array<float, 2>>(size)) {}

size_t Line::size() const
{
    return m_coord.size();
}

float const& Line::x(size_t it) const
{
    return m_coord.at(it).at(0);
}

float& Line::x(size_t it)
{
    return m_coord.at(it).at(0);
}

float const& Line::y(size_t it) const
{
    return m_coord.at(it).at(1);
}

float& Line::y(size_t it)
{
    return m_coord.at(it).at(1);
}
