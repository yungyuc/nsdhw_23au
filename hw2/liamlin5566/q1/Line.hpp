
#ifndef LINE_HPP
#define LINE_HPP

#include <vector>

class Line
{
public:
    Line() = default;
    Line(Line const & ); // copy constructor
    Line(Line       &&); //move constructor
    Line & operator=(Line const & ); // copy assignment operator
    Line & operator=(Line       &&); //move assignment operator
    Line(std::size_t size) {
        m_size = size;
        m_x.resize(size);
        m_y.resize(size);
        //a = 1;
    };
    ~Line() {};
    std::size_t size() const {return m_size; }
    float const & x(std::size_t it) const  {return m_x[it]; }
    float & x(std::size_t it) {return m_x[it]; }
    float const & y(std::size_t it) const {return m_y[it]; }
    float & y(std::size_t it) {return m_y[it]; }
private:
   std::size_t m_size;
   std::vector<float> m_x;
   std::vector<float> m_y;
}; /* end class Line */


#endif