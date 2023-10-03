#include <iostream>
#include <vector>


class Line
{
public:
    Line();
    Line(Line const &other);
    Line(Line       &&other);
    Line & operator=(Line const & );
    Line & operator=(Line       &&);
    Line(size_t size);
    ~Line();
    size_t size() const;
    float const & x(size_t it) const;
    float & x(size_t it);
    float const & y(size_t it) const;
    float & y(size_t it);
private:
    // Member data.
    std::vector<float> m_X;
    std::vector<float> m_Y;
}; /* end class Line */