#include <iostream>
#include <vector>

class Line
{
public:
    Line();
    Line(Line const & );
    Line(Line       &&);
    Line & operator=(Line const & );
    Line & operator=(Line       &&);
    Line(size_t size);
    ~Line();
    size_t size() const;
    const float & x(size_t it) const;
    float & x(size_t it);
    const float & y(size_t it) const;
    float & y(size_t it);
private:
    std::vector<float> vector_x;
    std::vector<float> vector_y;
}; 