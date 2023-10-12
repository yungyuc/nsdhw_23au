#pragma once

#include <cstdint>
#include <vector>

class Line {
public:
    Line() = default;
    Line(std::size_t size) : coord(size * 2) {}

    Line(const Line& line) = default;
    Line& operator=(const Line& line) = default;

    Line(Line&& line) = default;
    Line& operator=(Line&& line) = default;

    ~Line() = default;

    std::size_t size() const;

    const float& x(std::size_t index) const;
    float& x(std::size_t index);

    const float& y(std::size_t index) const;
    float& y(std::size_t index);

private:
    std::vector<float> coord;
};