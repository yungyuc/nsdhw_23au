#ifndef LINE_H
#define LINE_H

#include <vector>

class Line {
   public:
    Line() = default;
    Line(const Line &line) = default;
    Line(Line &&line) = default;
    Line &operator=(const Line &line) = default;
    Line &operator=(Line &&line) = default;
    Line(size_t n) : x_(n), y_(n) {}
    ~Line() = default;

    // Size
    size_t size() const { return x_.size(); }

    // Access
    double &x(size_t it) { return x_[it]; }
    double &y(size_t it) { return y_[it]; }
    const double &x(size_t it) const { return x_[it]; }
    const double &y(size_t it) const { return y_[it]; }

   private:
    std::vector<double> x_;
    std::vector<double> y_;

};

#endif