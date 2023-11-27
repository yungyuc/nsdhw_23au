#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>

template <class T>
class Allocator{
    public:

        typedef T value_type;

        Allocator() noexcept = default;

        Allocator(const Allocator &other) noexcept;

        template <class U>
        Allocator(const Allocator<U> &other) noexcept;

        ~Allocator() noexcept = default;

        template <class U>
        Allocator<T> &operator=(const Allocator<U> &other) noexcept;

        template <class U>
        bool operator==(const Allocator<U> &other) const noexcept;

        template <class U>
        struct rebind {
            typedef Allocator<U> other;
        };

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