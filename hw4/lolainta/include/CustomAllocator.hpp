#pragma once

#include <cstddef>
template <class T>
class CustomAllocator {
 public:
  using value_type = T;
  CustomAllocator() noexcept = default;
  template <class U>
  CustomAllocator(const CustomAllocator<U>&) noexcept;
  T* allocate(std::size_t n);
  void deallocate(T* p, std::size_t);
  static size_t bytes();
  static size_t allocated();
  static size_t deallocated();

 private:
  static size_t allocated_;
  static size_t deallocated_;
};
