#pragma once
#ifndef matrix__stl_HPP_
#define matrix__stl_HPP_


#include <cstddef>
#include <limits>
#include <new>


namespace matrix
{
class AllocatorMetrics
{
public:
    inline void alloc(std::size_t bytes)
    {
        m_bytes_allocated += bytes;
    }

    inline void dealloc(std::size_t bytes)
    {
        m_bytes_deallocated += bytes;
    }

    inline std::size_t bytes() const
    {
        return allocated() - deallocated();
    }

    inline std::size_t allocated() const
    {
        return m_bytes_allocated;
    }

    inline std::size_t deallocated() const
    {
        return m_bytes_deallocated;
    }

private:
    std::size_t m_bytes_allocated = 0;
    std::size_t m_bytes_deallocated = 0;
};

template<typename _Tp>
class CustomAllocator
{
public:
    using value_type = _Tp;

    inline value_type* allocate(std::size_t size)
    {
        if(size > std::numeric_limits<std::size_t>::max() / sizeof(value_type))
        {
            throw std::bad_alloc();
        }

        value_type* buffer = new value_type[size];
        if(buffer == nullptr)
        {
            throw std::bad_alloc();
        }

        m_metrics.alloc(size * sizeof(value_type));

        return buffer;
    }

    inline void deallocate(value_type* ptr, std::size_t size) noexcept
    {
        delete[] ptr;

        m_metrics.dealloc(size * sizeof(value_type));
    }

    static inline std::size_t bytes()
    {
        return m_metrics.bytes();
    }

    static inline std::size_t allocated()
    {
        return m_metrics.allocated();
    }

    static inline std::size_t deallocated()
    {
        return m_metrics.deallocated();
    }

private:
    // `static inline` needs C++17
    static inline AllocatorMetrics m_metrics = {};
};
}  // namespace matrix


#endif  // matrix__stl_HPP_
