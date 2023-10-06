#pragma once

#include <cstdint>
#include <vector>

class Line {
public:
    Line();
    Line(std::size_t size) : coord(size * 2) {}

    Line(const Line& line);
    Line& operator=(const Line& line);

    Line(Line&& line);
    Line& operator=(Line&& line);

    ~Line();

    std::size_t size() const;

    const float& x(std::size_t index) const;
    float& x(std::size_t index);

    const float& y(std::size_t index) const;
    float& y(std::size_t index);

private:
    std::vector<float> coord;
};