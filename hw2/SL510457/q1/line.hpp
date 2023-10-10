#include <vector>
#include <cstddef>

class Line
{
public:
    Line(size_t size);

    size_t size() const;

    float const & x(size_t it) const;
    float & x(size_t it);
    float const & y(size_t it) const;
    float & y(size_t it);

private:
    std::vector<float> x_cords;
    std::vector<float> y_cords;
};
