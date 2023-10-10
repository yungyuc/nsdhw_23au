#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Line
{
private:
    vector<pair<double, double>> points;

public:
    Line() = default;
    Line(Line const &) = default;
    Line(Line &&) = default;
    Line(size_t size)
    {
        points.resize(size);
    }
    Line &operator=(Line const &) = default;
    Line &operator=(Line &&) = default;
    size_t size() const
    {
        return points.size();
    }
    ~Line() = default;
    double const &x(size_t it) const
    {
        return points[it].first;
    }
    double &x(size_t it)
    {
        return points[it].first;
    }
    double const &y(size_t it) const
    {
        return points[it].second;
    }
    double &y(size_t it)
    {
        return points[it].second;
    }
};

int main(int, char **)
{
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
    for (size_t it = 0; it < line.size(); ++it)
    {
        std::cout << "point " << it << ":"
                  << " x = " << line.x(it)
                  << " y = " << line.y(it) << std::endl;
    }

    std::cout << "line2: number of points = " << line.size() << std::endl;
    for (size_t it = 0; it < line.size(); ++it)
    {
        std::cout << "point " << it << ":"
                  << " x = " << line2.x(it)
                  << " y = " << line2.y(it) << std::endl;
    }

    return 0;
}