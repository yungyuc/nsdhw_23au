#pragma once

#include <atomic>

struct ByteCounterImpl
{
    std::atomic_size_t allocated = {0};
    std::atomic_size_t deallocated = {0};
    std::atomic_size_t refcount = {0};
};

class ByteCounter
{
public:
    ByteCounter();
    ByteCounter(ByteCounter const &other);
    ByteCounter(ByteCounter &&other);

    ByteCounter &operator=(ByteCounter const &other);
    ByteCounter &operator=(ByteCounter &&other);

    ~ByteCounter();

    void swap(ByteCounter &other);
    void increase(std::size_t amount);
    void decrease(std::size_t amount);
    void recover_decrease(std::size_t amount);

    std::size_t bytes() const;
    std::size_t allocated() const;
    std::size_t deallocated() const;
    /* This is for debugging. */
    std::size_t refcount() const;

private:
    void incref();
    void decref();

    friend bool operator==(ByteCounter const &a, ByteCounter const &b);

    ByteCounterImpl *m_impl;

}; /* end class ByteCounter */