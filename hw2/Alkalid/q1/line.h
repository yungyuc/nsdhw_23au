#include <cstdint>
#include <vector>
#include <stdexcept>
// Class and function declarations
class Line
{
private:
    std::vector<int64_t> x_;
    std::vector<int64_t> y_;
public:
    // constructor
    Line(size_t );
    // copy constructor
    Line ( Line const &);
    // copy assignment operator
    Line & operator=(Line const &)=delete;
    // move assigment operator
    Line & operator=(Line &&)=delete;
    // move constructor
    Line (Line &&)=delete;
    // destructor
    ~Line();

    int64_t & x(size_t);
    int64_t & y(size_t);
    size_t size();
};