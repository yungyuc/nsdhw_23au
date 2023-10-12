#pragma once
#include <cstddef> // size_t
#include <vector>
#include <utility> // pair
class Line
{
private:
    std::vector<std::pair<float, float>> _points;

public:
    Line() = default;
    Line(Line const &) = default;
    Line(Line &&) = default;
    Line &operator=(Line const &) = default;
    Line &operator=(Line &&) = default;
    Line(size_t size);
    ~Line() = default;
    size_t size() const;
    float const &x(size_t it) const;
    float &x(size_t it);
    float const &y(size_t it) const;
    float &y(size_t it);
};
