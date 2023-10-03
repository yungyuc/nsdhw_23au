#include "Line.hpp"

// copy constructor
Line::Line(const Line &line) : m_size(line.m_size), m_x(line.m_x), m_y(line.m_y) {}

// move constructor
Line::Line(Line &&line)
{
    // Can be replaced with std::move 
    m_size = line.m_size;
    m_x = line.m_x;
    m_y = line.m_y;

    line.m_size = 0;
    line.m_x = std::vector<float>();
    line.m_y = std::vector<float>();
}


// copy assignment operator
Line &Line::operator=(Line const &line)
{   
    // self-assignment check
    if (this != &line)
    {
        m_size = line.m_size;
        m_x = line.m_x;
        m_y = line.m_y;
    }
    return *this;
}


// move assignment operator
Line &Line::operator=(Line &&line)
{
    // Can be replaced with std::move 
    if (this != &line)
    {
        m_size = line.m_size;
        m_x = line.m_x;
        m_y = line.m_y;

        line.m_size = 0;
        line.m_x = std::vector<float>();
        line.m_y = std::vector<float>();
    }
    return *this;
}