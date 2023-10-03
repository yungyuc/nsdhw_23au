#include "line.hpp"

// Implement the member functions here.

Line::Line() {}

Line::~Line() {}

Line::Line(size_t size) {
    // Initialize this Line with the specified size
    m_X.resize(size);
    m_Y.resize(size);
}

Line::Line(Line &&other) {
    // Move the data and size from the other Line
    m_X = std::move(other.m_X);
    m_Y = std::move(other.m_Y);
}

Line & Line::operator=(const Line &other) {
    if (this != &other) {
        // 复制另一个 Line 对象的大小
        size_t otherSize = other.size();

        // 调整此 Line 的大小以匹配另一个 Line 的大小
        m_X.resize(otherSize);
        m_Y.resize(otherSize);

        // 复制另一个 Line 的数据
        for (size_t i = 0; i < otherSize; ++i) {
            m_X[i] = other.m_X[i];
            m_Y[i] = other.m_Y[i];
        }
    }
    return *this;
}

Line & Line::operator=(Line &&other) {
    if (this != &other) {
        // 移动另一个 Line 对象的数据和大小
        m_X = std::move(other.m_X);
        m_Y = std::move(other.m_Y);
    }
    return *this;
}


Line::Line(const Line &other) {
    // Copy the size of the other Line
    size_t otherSize = other.size();

    // Resize this Line to match the size of the other Line
    m_X.resize(otherSize);
    m_Y.resize(otherSize);

    // Copy the data from the other Line
    for (size_t i = 0; i < otherSize; ++i) {
        m_X[i] = other.m_X[i];
        m_Y[i] = other.m_Y[i];
    }
}

size_t Line::size() const {return m_X.size();}



float const &Line::x(size_t it) const { return m_X[it];}
//need return

float &Line::x(size_t it) {
    // Implementation of the x() function for non-const access.
    return m_X[it];
}
//need return
float const &Line::y(size_t it) const {
    // Implementation of the y() function.
    return m_Y[it];
}
//need return
float &Line::y(size_t it) {
    // Implementation of the y() function for non-const access.
    return m_Y[it];
}

// Implement the remaining member functions as needed.
int main(int, char **)
{
    Line line(3);
    line.x(0) = 0; line.y(0) = 1;
    line.x(1) = 1; line.y(1) = 3;
    line.x(2) = 2; line.y(2) = 5;

    Line line2(line);
    line2.x(0) = 9;

    std::cout << "line: number of points = " << line.size() << std::endl;
    for (size_t it=0; it<line.size(); ++it)
    {
        std::cout << "point " << it << ":"
                  << " x = " << line.x(it)
                  << " y = " << line.y(it) << std::endl;
    }

    std::cout << "line2: number of points = " << line.size() << std::endl;
    for (size_t it=0; it<line.size(); ++it)
    {
        std::cout << "point " << it << ":"
                  << " x = " << line2.x(it)
                  << " y = " << line2.y(it) << std::endl;
    }

    return 0;
}