#pragma once
#ifndef Q1__LINE_HPP_
#define Q1__LINE_HPP_

/**
 * @brief Line
 */

#include<array>
#include<vector>

/**
 * @brief A line
 */
class Line
{
public:
    Line() = default;
    Line(Line const&) = default;
    Line(Line&&) = default;
    Line& operator=(Line const&) = default;
    Line& operator=(Line&&) = default;
    Line(size_t size);
    ~Line() = default;

    size_t size() const;
    float const& x(size_t it) const;
    float& x(size_t it);
    float const& y(size_t it) const;
    float& y(size_t it);

private:
    // Memory buffer for the points
    std::vector<std::array<float, 2>> m_coord;
};

#endif  // Q1__LINE_HPP_
