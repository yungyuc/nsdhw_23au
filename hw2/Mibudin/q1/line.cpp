#include"line.hpp"

Line::Line(std::size_t size)
    : m_coord(std::vector<std::array<float, 2>>(size)) {}

std::size_t Line::size() const
{
    return m_coord.size();
}

float const& Line::x(std::size_t it) const
{
    return m_coord.at(it).at(0);
}

float& Line::x(std::size_t it)
{
    return m_coord.at(it).at(0);
}

float const& Line::y(std::size_t it) const
{
    return m_coord.at(it).at(1);
}

float& Line::y(std::size_t it)
{
    return m_coord.at(it).at(1);
}
