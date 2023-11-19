#ifndef _ALLOCATOR_HPP_
#define _ALLOCATOR_HPP_

#include <cstdlib>
#include <new>
#include <memory>
#include <limits>
#include <atomic>
#include <vector>
#include <iostream>

struct ByteCounterImpl{
    std::atomic_size_t allocated{0};
    std::atomic_size_t deallocated{0};
    std::atomic_size_t refcount{0};
};

class ByteCounter{
public:
    ByteCounter();
    ByteCounter(ByteCounter const & other);
    ByteCounter & operator=(ByteCounter const & other);
    ByteCounter(ByteCounter && other);
    ByteCounter & operator=(ByteCounter && other);
    ~ByteCounter();
    void swap(ByteCounter & other);
    void increase(std::size_t amount);
    void decrease(std::size_t amount);
    std::size_t bytes() const;
    std::size_t allocated() const; 
    std::size_t deallocated() const;
    std::size_t refcount() const; 

private:
    void incref();
    void decref();
    ByteCounterImpl * m_impl;
};

template <class T>
struct CustomAllocator
{
    ByteCounter counter;
    using value_type = T;

    CustomAllocator() = default;

    template <class U>
    constexpr CustomAllocator(const CustomAllocator<U> &other) noexcept: counter(other.counter){}

    T * allocate(std::size_t n){
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)){
            throw std::bad_alloc();
        }
        const std::size_t bytes = n*sizeof(T);
        T * p = static_cast<T *>(std::malloc(bytes));
        if (p){
            counter.increase(bytes);
            return p;
        }
        else{
            throw std::bad_alloc();
        }
    }

    void deallocate(T* p, std::size_t n) noexcept{
        std::free(p);
        const std::size_t bytes = n*sizeof(T);
        counter.decrease(bytes);
    }

}; // struct CustomAllocator

#endif