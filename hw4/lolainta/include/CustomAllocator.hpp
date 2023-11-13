#pragma once

#include <cstddef>
template <class T>
class CustomAllocator {
 public:
  using value_type = T;
  CustomAllocator() noexcept = default;
  template <class U>
  CustomAllocator(const CustomAllocator<U>&) noexcept;
  T* allocate(std::size_t);
  void deallocate(T*, std::size_t);
  static size_t bytes() noexcept;
  static size_t allocated() noexcept;
  static size_t deallocated() noexcept;

 private:
  static size_t allocated_;
  static size_t deallocated_;
};
