#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>

template <class T>
class Allocator{
    public:

        typedef T value_type;

        Allocator() noexcept = default;

        template <class U>
        Allocator(const Allocator<U> &other) noexcept;

        ~Allocator() noexcept = default;

        T *allocate(std::size_t n);

        void deallocate(T *p, std::size_t n);

        static int bytes() noexcept;
        static int allocated() noexcept;
        static int deallocated() noexcept;
    private:
        static int allocated_;
        static int deallocated_;
};


#endif