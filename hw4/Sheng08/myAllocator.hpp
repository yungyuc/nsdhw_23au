#ifndef _myAllocator_H_
#define _myAllocator_H_

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct ByteCounterImpl {
    size_t allocated = 0;
    size_t deallocated = 0;
}; /* end struct ByteCounterImpl */

class ByteCounter {

public:
    ByteCounter()
        : m_impl(new ByteCounterImpl) {}

    ByteCounter(ByteCounter const &other)
        : m_impl(other.m_impl) {}

    ByteCounter &operator=(ByteCounter const &other) {
        if (&other != this) {
            m_impl = other.m_impl;
        }

        return *this;
    }

    ByteCounter(ByteCounter &&other)
        : m_impl(other.m_impl) {}

    ByteCounter &operator=(ByteCounter &&other) {
        if (&other != this) {
            m_impl = other.m_impl;
        }

        return *this;
    }

    ~ByteCounter() {}

    void swap(ByteCounter &other) {
        std::swap(m_impl, other.m_impl);
    }

    void increase(size_t amount) {
        m_impl->allocated += amount;
    }

    void decrease(size_t amount) {
        m_impl->deallocated += amount;
    }

    size_t bytes() const { return m_impl->allocated - m_impl->deallocated; }
    size_t allocated() const { return m_impl->allocated; }
    size_t deallocated() const { return m_impl->deallocated; }

private:
    ByteCounterImpl *m_impl;
};

bool operator==(const ByteCounter &a, const ByteCounter &b) {
    return a == b;
}

template <class T>
struct myAllocator {
    using value_type = T;

    myAllocator() = default;

    template <class U>
    constexpr myAllocator(const myAllocator<U> &other) noexcept {
        counter = other.counter;
    }

    T *allocate(size_t n) {
        if (n > numeric_limits<size_t>::max() / sizeof(T)) {
            throw std::bad_alloc();
        }
        const size_t bytes = n * sizeof(T);
        T *p = static_cast<T *>(std::malloc(bytes));
        if (p) {
            counter.increase(bytes);

            return p;
        } else {
            throw std::bad_alloc();
        }
    }

    void deallocate(T *p, size_t n) noexcept {
        std::free(p);

        const size_t bytes = n * sizeof(T);
        counter.decrease(bytes);
    }

    ByteCounter counter;
}; /* end struct myAllocator */

template <class T, class U>
bool operator==(const myAllocator<T> &a, const myAllocator<U> &b) {
    return a.counter == b.counter;
}

template <class T, class U>
bool operator!=(const myAllocator<T> &a, const myAllocator<U> &b) {
    return !(a == b);
}

template <class T>
std::ostream &operator<<(std::ostream &out, const myAllocator<T> &alloc) {
    out << "allocator: bytes = " << alloc.counter.bytes();
    out << " allocated = " << alloc.counter.allocated();
    out << " deallocated =  " << alloc.counter.deallocated();
    return out;
}

#endif