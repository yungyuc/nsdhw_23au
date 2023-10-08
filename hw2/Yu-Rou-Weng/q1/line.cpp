#include <vector>
#include <iostream>
using namespace std;

class Line
{
public:
    Line() = default;
    Line(size_t size) : x_(size), y_(size) {}

    size_t size() const { return x_.size(); }

    void setPoint(size_t index, float x, float y)
    {
        if (index < x_.size())
        {
            x_[index] = x;
            y_[index] = y;
        }
    }

    float getX(size_t index) const
    {
        return (index < x_.size()) ? x_[index] : 0.0f;
    }

    float getY(size_t index) const
    {
        return (index < y_.size()) ? y_[index] : 0.0f;
    }

private:
    vector<float> x_;
    vector<float> y_;
};

int main(int, char **)
{
    Line line(3);
    line.setPoint(0, 0, 1);
    line.setPoint(1, 1, 3);
    line.setPoint(2, 2, 5);

    Line line2(line);
    line2.setPoint(0, 9, line.getY(0)); 
    cout << "line: number of points = " << line.size() << endl;
    for (size_t it = 0; it < line.size(); ++it)
    {
        cout << "point " << it << ":"
             << " x = " << line.getX(it)
             << " y = " << line.getY(it) << endl;
    }

    cout << "line2: number of points = " << line.size() << endl;
    for (size_t it = 0; it < line.size(); ++it)
    {
        cout << "point " << it << ":"
             << " x = " << line2.getX(it)
             << " y = " << line2.getY(it) << endl;
    }
    return 0;
}
