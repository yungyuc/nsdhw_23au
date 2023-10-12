#include "line.hpp"

#include <cstdint>

auto Line::size() const -> std::size_t { return coord.size() / 2; }

auto Line::x(std::size_t index) const -> const float& {
    return coord[index * 2];
}

auto Line::x(std::size_t index) -> float& { return coord[index * 2]; }

auto Line::y(std::size_t index) const -> const float& {
    return coord[index * 2 + 1];
}

auto Line::y(std::size_t index) -> float& { return coord[index * 2 + 1]; }
