#pragma once

#include <vector>
#include <iostream>
using namespace std;

class Line {
    public:
        // Default Constructor
        Line(){}

        // Copy Constructor
        Line(Line const &  line):
            _x(line._x), _y(line._y){}

        Line(Line       && line):
            _x(move(line._x)), _y(move(line._y)){}
        
        Line & operator = (Line const &  line) {
            _x = line._x;
            _y = line._y;
            return *this;
        }

        Line & operator = (Line       && line) {
            _x = move(line._x);
            _y = move(line._y);
            return *this;
        }

        // Parameterized Constructor
        Line(size_t size): _x(size),_y(size){}

        ~Line(){}
        
        size_t size() const {
            return _x.size();
        }

        float const & x(size_t it) const {
            return _x.at(it);
        }

        float & x(size_t it) {
            return _x.at(it);
        }

        float const & y(size_t it) const {
            return _y.at(it);
        }

        float & y(size_t it) {
            return _y.at(it);
        }
        

    private:
        // Member data.
        vector<float> _x;
        vector<float> _y;

}; /* end class Line */