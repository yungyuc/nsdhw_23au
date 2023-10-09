#ifndef LINE_H
#define LINE_H

#include <cstddef>
#include <vector>

using namespace std;

class Line
{
public:
    Line();
    Line(Line const & );
    // Line(Line       &&);
    // Line & operator=(Line const & );
    // Line & operator=(Line       &&);
    Line(size_t size);
    ~Line();
    size_t size() const;
    float const & x(size_t it) const;
    float & x(size_t it);
    float const & y(size_t it) const;
    float & y(size_t it);
private:
    // Member data.
    vector<float> m_x, m_y;
    size_t m_size;
}; /* end class Line */

#endif