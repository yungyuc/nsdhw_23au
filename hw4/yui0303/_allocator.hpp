#ifndef _ALLOCATOR_HPP_
#define _ALLOCATOR_HPP_

#include <cstdlib>
#include <new>
#include <memory>
#include <limits>
#include <atomic>
#include <vector>
#include <iostream>

struct ByteCounterImpl
{
    std::atomic_size_t allocated{0};
    std::atomic_size_t deallocated{0};
    std::atomic_size_t refcount{0};

}; /* end struct ByteCounterImpl */

/**
 * One instance of this counter is shared among a set of allocators.
 *
 * The counter keeps track of the bytes allocated and deallocated, and report
 * those two numbers in addition to bytes that remain allocated.
 */
class ByteCounter
{

public:

    ByteCounter()
      : m_impl(new ByteCounterImpl)
    { incref(); }

    ByteCounter(ByteCounter const & other)
      : m_impl(other.m_impl)
    { incref(); }

    ByteCounter & operator=(ByteCounter const & other)
    {
        if (&other != this)
        {
            decref();
            m_impl = other.m_impl;
            incref();
        }

        return *this;
    }

    ByteCounter(ByteCounter && other)
      : m_impl(other.m_impl)
    { incref(); }

    ByteCounter & operator=(ByteCounter && other)
    {
        if (&other != this)
        {
            decref();
            m_impl = other.m_impl;
            incref();
        }

        return *this;
    }

    ~ByteCounter() { decref(); }

    void swap(ByteCounter & other)
    {
        std::swap(m_impl, other.m_impl);
    }

    void increase(std::size_t amount)
    {
        m_impl->allocated += amount;
    }

    void decrease(std::size_t amount)
    {
        m_impl->deallocated += amount;
    }

    std::size_t bytes() const { return m_impl->allocated - m_impl->deallocated; }
    std::size_t allocated() const { return m_impl->allocated; }
    std::size_t deallocated() const { return m_impl->deallocated; }
    /* This is for debugging. */
    std::size_t refcount() const { return m_impl->refcount; }

private:

    void incref() { ++m_impl->refcount; }

    void decref()
    {
        if (nullptr == m_impl)
        {
            // Do nothing.
        }
        else if (1 == m_impl->refcount)
        {
            delete m_impl;
            m_impl = nullptr;
        }
        else
        {
            --m_impl->refcount;
        }
    }

    // friend bool operator==(ByteCounter const & a, ByteCounter const & b);

    ByteCounterImpl * m_impl;

}; /* end class ByteCounter */

// bool operator==(ByteCounter const & a, ByteCounter const & b)
// {
//     return a.m_impl == b.m_impl;
// }

/**
 * Very simple allocator that counts the number of bytes allocated through it.
 *
 * It's made to demonstrate the STL allocator and only works in this example.
 * A lot of modification is needed to use it in a real application.
 */
template <class T>
struct CustomAllocator
{

    using value_type = T;

    // Just use the default constructor of ByteCounter for the data member
    // "counter".
    CustomAllocator() = default;

    template <class U>
    constexpr CustomAllocator(const CustomAllocator<U> &other) noexcept
        : counter(other.counter)
        {}

    T * allocate(std::size_t n)
    {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
        {
            throw std::bad_alloc();
        }
        const std::size_t bytes = n*sizeof(T);
        T * p = static_cast<T *>(std::malloc(bytes));
        if (p)
        {
            counter.increase(bytes);
            return p;
        }
        else
        {
            throw std::bad_alloc();
        }
    }

    void deallocate(T* p, std::size_t n) noexcept
    {
        std::free(p);

        const std::size_t bytes = n*sizeof(T);
        counter.decrease(bytes);
    }

    ByteCounter counter;

}; /* end struct CustomAllocator */

// template <class T, class U>
// bool operator==(const CustomAllocator<T> & a, const CustomAllocator<U> & b)
// {
//     return a.counter == b.counter;
// }

// template <class T, class U>
// bool operator!=(const CustomAllocator<T> & a, const CustomAllocator<U> & b)
// {
//     return !(a == b);
// }

// template <class T>
// std::ostream & operator << (std::ostream & out, const CustomAllocator<T> & alloc)
// {
//     out << "allocator: bytes = " << alloc.counter.bytes();
//     out << " allocated = " << alloc.counter.allocated();
//     out << " deallocated = " << alloc.counter.deallocated();
//     return out;
// }

#endif