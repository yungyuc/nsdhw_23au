#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct ByteCounterImpl
{
    size_t allocated = 0;
    size_t deallocated = 0;
};

class ByteCounter
{

public:
    ByteCounter()
        : m_impl(new ByteCounterImpl)
    {
    }

    ByteCounter(ByteCounter const &other)
        : m_impl(other.m_impl)
    {
    }
    ByteCounter &operator=(ByteCounter const &other)
    {
        if (&other != this)
        {
            m_impl = other.m_impl;
        }

        return *this;
    }
    ByteCounter(ByteCounter &&other)
        : m_impl(other.m_impl)
    {
    }
    ByteCounter &operator=(ByteCounter &&other)
    {
        if (&other != this)
        {
            m_impl = other.m_impl;
        }

        return *this;
    }

    ~ByteCounter()
    {
    }

    void increase(size_t count)
    {
        m_impl->allocated += count;
    }

    void decrease(size_t count)
    {
        m_impl->deallocated += count;
    }

    size_t bytes() const { return m_impl->allocated - m_impl->deallocated; }
    size_t allocated() const { return m_impl->allocated; }
    size_t deallocated() const { return m_impl->deallocated; }

private:
    ByteCounterImpl *m_impl;
};

bool operator==(const ByteCounter &a, const ByteCounter &b)
{
    return a == b;
}

template <class T>
struct CustomAllocator
{
    using value_type = T;

    CustomAllocator() = default;

    template <class U>
    CustomAllocator(const CustomAllocator<U> &other) noexcept
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
};

template <class T, class U>
bool operator==(const CustomAllocator<T> &a, const CustomAllocator<U> &b)
{
    return a.counter == b.counter;
}

template <class T, class U>
bool operator!=(const CustomAllocator<T> &a, const CustomAllocator<U> &b)
{
    return !(a == b);
}

CustomAllocator<double> allocate;

size_t bytes()
{
    return allocate.counter.allocated() - allocate.counter.deallocated();
}

size_t allocated()
{
    return allocate.counter.allocated();
}

size_t deallocated()
{
    return allocate.counter.deallocated();
}

class Matrix
{

public:
    Matrix()
        : m_nrow(0), m_ncol(0)
    {
    }

    Matrix(size_t nrow, size_t ncol)
        : m_nrow(nrow), m_ncol(ncol)
    {
        m_buffer.resize(m_nrow * m_ncol);
    }

    ~Matrix()
    {
        m_buffer.clear();
    }

    Matrix(const Matrix &other)
        : m_nrow(other.nrow()), m_ncol(other.ncol()), m_buffer(other.m_buffer)
    {
    }

    Matrix &operator=(Matrix const &other)
    {
        if (this == &other)
        {
            return *this;
        }

        m_nrow = other.nrow();
        m_ncol = other.ncol();
        m_buffer = other.m_buffer;

        return *this;
    }

    Matrix(Matrix &&other)
        : m_nrow(other.nrow()), m_ncol(other.ncol()), m_buffer(move(other.m_buffer))
    {
    }

    Matrix &operator=(Matrix &&other)
    {
        if (this == &other)
        {
            return *this;
        }

        m_nrow = other.nrow();
        m_ncol = other.ncol();
        m_buffer = other.m_buffer;

        return *this;
    }

    double operator()(size_t row, size_t col) const
    {
        return m_buffer[row * m_ncol + col];
    }
    double &operator()(size_t row, size_t col)
    {
        return m_buffer[row * m_ncol + col];
    }

    bool operator==(const Matrix &other) const
    {
        return m_buffer == other.m_buffer;
    }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }

    double buffer(size_t i) const { return m_buffer[i]; }

    double *data() { return &m_buffer[0]; }

private:
    vector<double, CustomAllocator<double>> m_buffer{allocate};
    size_t index(size_t row, size_t col) const { return row * m_ncol + col; }
    size_t m_nrow;
    size_t m_ncol;
};

#endif