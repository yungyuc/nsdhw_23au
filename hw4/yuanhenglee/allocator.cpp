#include "allocator.h"

#include <cstddef>
#include <cstdlib>
#include <new> 

template class Allocator<double>;

template <class T>
int Allocator<T>::allocated_ = 0;

template <class T>
int Allocator<T>::deallocated_ = 0;

template <class T>
Allocator<T>::Allocator(const Allocator &other) noexcept {
    allocated_ = other.allocated();
    deallocated_ = other.deallocated();
}

template <class T>
template <class U>
Allocator<T>::Allocator(const Allocator<U> &other) noexcept {
    allocated_ = other.allocated();
    deallocated_ = other.deallocated();
}

template <class T>
template <class U>
Allocator<T> &Allocator<T>::operator=(const Allocator<U> &other) noexcept {
    allocated_ = other.allocated();
    deallocated_ = other.deallocated();
    return *this;
}

template <class T>
T *Allocator<T>::allocate(std::size_t n) {
    if ( auto p = static_cast<T *>( malloc(n * sizeof(T)) ) ) {
        allocated_ += n * sizeof(T);
        return p;
    }
    throw std::bad_alloc();
}

template <class T>
void Allocator<T>::deallocate(T *p, std::size_t n) {
    deallocated_ += n * sizeof(T);
    free(p);
}

template <class T>
int Allocator<T>::bytes() noexcept {
    return (allocated_ - deallocated_);
}

template <class T>
int Allocator<T>::allocated() noexcept {
    return allocated_;
}

template <class T>
int Allocator<T>::deallocated() noexcept {
    return deallocated_;
}


