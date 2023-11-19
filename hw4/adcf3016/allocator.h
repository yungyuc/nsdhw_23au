#ifndef _CUSTOM_ALLOCAOTR_H
#define _CUSTOM_ALLOCAOTR_H

#include <atomic>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <vector>

struct ByteCounterImpl {
    std::size_t allocated = 0;
    std::size_t deallocated = 0;
    std::size_t refcount = 0;
};

/**
 * One instance of this counter is shared among a set of allocators.
 *
 * The counter keeps track of the bytes allocated and deallocated, and report
 * those two numbers in addition to bytes that remain allocated.
 */
class ByteCounter {
   public:
    ByteCounter()
        : m_impl(new ByteCounterImpl) { incref(); }

    ByteCounter(ByteCounter const &other)
        : m_impl(other.m_impl) { incref(); }

    ByteCounter &operator=(ByteCounter const &other) {
        if (&other != this) {
            decref();
            m_impl = other.m_impl;
            incref();
        }
        return *this;
    }

    ByteCounter(ByteCounter &&other)
        : m_impl(other.m_impl) { other.incref(); }

    ByteCounter &operator=(ByteCounter &&other) {
        if (&other != this) {
            decref();
            m_impl = other.m_impl;
        }
        return *this;
    }

    ~ByteCounter() { decref(); }

    void swap(ByteCounter &other) {
        std::swap(m_impl, other.m_impl);
    }

    void increase(std::size_t amount) {
        m_impl->allocated += amount;
    }

    void decrease(std::size_t amount) {
        m_impl->deallocated += amount;
    }

    std::size_t bytes() const { return m_impl->allocated - m_impl->deallocated; }
    std::size_t allocated() const { return m_impl->allocated; }
    std::size_t deallocated() const { return m_impl->deallocated; }
    /* This is for debugging. */
    // std::size_t refcount() const { return m_impl->refcount; }

   private:
    void incref() {
        ++m_impl->refcount;
    }

    void decref() {
        if (nullptr == m_impl)
            return;
        else if (1 == m_impl->refcount) {
            delete m_impl;
            m_impl = nullptr;
        } else {
            --m_impl->refcount;
        }
    }

    ByteCounterImpl *m_impl;
};

template <class T>
struct CustomAllocator {
    using value_type = T;
    CustomAllocator() = default;

    template <class U>
    constexpr CustomAllocator(const CustomAllocator<U> &other) noexcept : counter(other.counter){};

    T *allocate(std::size_t n) {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
            throw std::bad_alloc();
        }
        const std::size_t bytes = n * sizeof(T);
        T *ptr = (T *)std::malloc(bytes);
        if (ptr) {
            counter.increase(bytes);
            return ptr;
        } else {
            throw std::bad_alloc();
        }
    }

    void deallocate(T *p, std::size_t n) noexcept {
        std::free(p);

        const std::size_t bytes = n * sizeof(T);
        counter.decrease(bytes);
    }

    std::size_t bytes() const { return counter.bytes(); }
    std::size_t allocated() const { return counter.allocated(); }
    std::size_t deallocated() const { return counter.deallocated(); }

    ByteCounter counter;
};

#endif
