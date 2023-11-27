#ifndef MATRIX_H
#define MATRIX_H

#include <bits/stdc++.h>
#include <vector>
#include <cstddef>

template<typename T>
class CustomAllocator {
public:
    using value_type = T;
    CustomAllocator() = default;
    T* allocate(std::size_t sz);
    void deallocate(T *ptr, std::size_t sz);

    static size_t getAllocated() { return m_allocated; }
    static size_t getDeallocated() { return m_deallocated; }
    static size_t getBytes() { return m_allocated - m_deallocated; }

private:
    static size_t m_allocated, m_deallocated;
};

template <class T> size_t CustomAllocator<T>::m_allocated = 0.0;
template <class T> size_t CustomAllocator<T>::m_deallocated = 0.0;


class Matrix {
public:
    Matrix() = default;
    // ~Matrix();
    Matrix(size_t, size_t);

    double operator() (size_t, size_t) const;
    double& operator() (size_t, size_t);
    bool operator==(const Matrix&) const;
    bool operator!=(const Matrix&) const;

    void resetBuffer();

    const size_t& n_row() const;
    const size_t& n_col() const;
    double *m_buffers() const;
private:
    size_t m_row;
    size_t m_col;
    std::vector<double, CustomAllocator<double>> m_buffer;
};

#endif