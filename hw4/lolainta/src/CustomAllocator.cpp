#include "CustomAllocator.hpp"

#include <cstdlib>
#include <new>

template class CustomAllocator<double>;

template <class T>
size_t CustomAllocator<T>::allocated_ = 0;
template <class T>
size_t CustomAllocator<T>::deallocated_ = 0;

template <class T>
size_t CustomAllocator<T>::bytes() noexcept {
  return allocated_ - deallocated_;
}

template <class T>
size_t CustomAllocator<T>::allocated() noexcept {
  return allocated_;
}

template <class T>
size_t CustomAllocator<T>::deallocated() noexcept {
  return deallocated_;
}

template <class T>
T *CustomAllocator<T>::allocate(std::size_t n) {
  if (n > std::size_t(-1) / sizeof(T)) {
    throw std::bad_alloc();
  }
  if (auto p = static_cast<T *>(std::malloc(n * sizeof(T)))) {
    allocated_ += sizeof(T) * n;
    return p;
  }
  throw std::bad_alloc();
}

template <class T>
void CustomAllocator<T>::deallocate(T *p, std::size_t n) {
  deallocated_ += sizeof(T) * n;
  std::free(p);
}

template <class T>
template <class U>
CustomAllocator<T>::CustomAllocator(const CustomAllocator<U> &o) noexcept {
  allocated_ = o.allocated_;
  deallocated_ = o.deallocated_;
}
