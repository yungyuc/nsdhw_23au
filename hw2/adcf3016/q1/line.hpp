#include <cstddef>
#include <vector>

class Line {
   public:
    Line();
    Line(Line const &);
    Line(Line &&);
    Line &operator=(Line const &);
    Line &operator=(Line &&);
    Line(size_t size);
    ~Line();
    size_t size() const;
    float const &x(size_t it) const;
    float &x(size_t it);
    float const &y(size_t it) const;
    float &y(size_t it);

   private:
    std::vector<float> m_x;
    std::vector<float> m_y;
};
