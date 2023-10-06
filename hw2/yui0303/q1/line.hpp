#ifndef __LINE_HPP__
#define __LINE_HPP__

#include <iostream>
#include <vector>
#include <utility>

class Line
{
public:
    Line() = default; // default constructor
    Line(Line const & ); // copy constructor
    Line(Line       &&); // move constructor
    Line & operator=(Line const & ); //copy assignment operator
    Line & operator=(Line       &&); //move assignment operator
    Line(size_t size); // value constructor
    ~Line(); // destructor
    size_t size() const;
    float const & x(size_t it) const;
    float & x(size_t it);
    float const & y(size_t it) const;
    float & y(size_t it);
private:  
    std::vector<std::pair<float, float>> points; 
}; 

#endif