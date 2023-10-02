#include <iostream>
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

int main(int, char **) {
    Line line(3);
    line.x(0) = 0;
    line.y(0) = 1;
    line.x(1) = 1;
    line.y(1) = 3;
    line.x(2) = 2;
    line.y(2) = 5;

    Line line2(line);
    line2.x(0) = 9;

    std::cout << "line: number of points = " << line.size() << std::endl;
    for (size_t it = 0; it < line.size(); ++it) {
        std::cout << "point " << it << ":"
                  << " x = " << line.x(it) << " y = " << line.y(it)
                  << std::endl;
    }

    std::cout << "line2: number of points = " << line.size() << std::endl;
    for (size_t it = 0; it < line.size(); ++it) {
        std::cout << "point " << it << ":"
                  << " x = " << line2.x(it) << " y = " << line2.y(it)
                  << std::endl;
    }

    return 0;
}