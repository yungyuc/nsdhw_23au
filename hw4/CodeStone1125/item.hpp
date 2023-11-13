#include <cstdlib>
#include <iostream>
#include <atomic>
#include <vector>
#include <new>
#include <memory>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;
// based on https://yyc.solvcon.net/en/latest/nsd/07mem/example.html#nsd-mem-example-alloc

struct ByteCounterImpl
{
    size_t allocated = 0;
    size_t deallocated = 0;
    size_t refcount = 0;
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

    void increase(size_t amount)
    {
        m_impl->allocated += amount;
    }

    void decrease(size_t amount)
    {
        m_impl->deallocated += amount;
    }

    size_t bytes() const { return m_impl->allocated - m_impl->deallocated; }
    size_t allocated() const { return m_impl->allocated; }
    size_t deallocated() const { return m_impl->deallocated; }
    /* This is for debugging. */
    size_t refcount() const { return m_impl->refcount; }

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

    ByteCounterImpl * m_impl;

}; /* end class ByteCounter */

/*
 * Very simple allocator that counts the number of bytes allocated through it.
 */
template <class T>
struct MyAllocator
{

    using value_type = T;

    // Just use the default constructor of ByteCounter for the data member
    // "counter".
    MyAllocator() = default;

    template <class U> 
    constexpr MyAllocator(const MyAllocator<U> & other) noexcept
    {
        counter = other.counter;
    }

    T *allocate(size_t n)
    {
        if (n > numeric_limits<size_t>::max() / sizeof(T))
        {
            throw bad_alloc();
        }
        const size_t bytes = n * sizeof(T);
        T *p = static_cast<T *>(malloc(bytes));
        if (p)
        {
            counter.increase(bytes);
            return p;
        }
        else
        {
            throw bad_alloc();
        }
    }


    void deallocate(T *p, size_t n) noexcept
    {
        free(p);

        const size_t bytes = n * sizeof(T);
        counter.decrease(bytes);
    }

    ByteCounter counter;

}; /* end struct MyAllocator */