#include "line.h"

// Constructor
Line::Line(size_t size) {
    x_.resize(size,0);
    y_.resize(size,0);
}

Line::Line(Line const & other_line) {
    x_=other_line.x_;
    y_=other_line.y_;
}

// Return a reference to the x-coordinate at the given index
int64_t & Line::x(size_t index) {
    return x_.at(index); // 使用 at 來進行邊界檢查
}

// Return a reference to the y-coordinate at the given index
int64_t & Line::y(size_t index) {
    return y_.at(index); // 使用 at 來進行邊界檢查
}

// Return the size (number of points) of the line
size_t Line::size() {
    return x_.size();
}
Line::~Line(){
    x_.clear();
    y_.clear();
}