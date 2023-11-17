#include <iostream>

struct Byte_Counter_Impl
{
    std::atomic_size_t allocated{0};
    std::atomic_size_t deallocated{0};
    std::atomic_size_t refcount{0};
};

class Byte_Counter
{
public:
    Byte_Counter()
        : m_impl(new Byte_Counter_Impl)
    {
        incref();
    }

    Byte_Counter(Byte_Counter const &other)
        : m_impl(other.m_impl)
    {
        incref();
    }

    Byte_Counter &operator=(Byte_Counter const &other)
    {
        if (&other != this)
        {
            decref();
            m_impl = other.m_impl;
            incref();
        }

        return *this;
    }

    Byte_Counter(Byte_Counter &&other)
        : m_impl(other.m_impl)
    {
        incref();
    }

    Byte_Counter &operator=(Byte_Counter &&other)
    {
        if (&other != this)
        {
            decref();
            m_impl = other.m_impl;
            incref();
        }

        return *this;
    }

    ~Byte_Counter() { decref(); }

    void swap(Byte_Counter &other)
    {
        std::swap(m_impl, other.m_impl);
    }

    void increase(std::size_t amount)
    {
        m_impl->allocated += amount;
    }

    void decrease(std::size_t amount)
    {
        m_impl->deallocated += amount;
    }

    std::size_t bytes() const
    {
        return m_impl->allocated - m_impl->deallocated;
    }

    std::size_t allocated() const
    {
        return m_impl->allocated;
    }

    std::size_t deallocated() const
    {
        return m_impl->deallocated;
    }

    /* This is for debugging. */
    std::size_t refcount() const
    {
        return m_impl->refcount;
    }

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

    Byte_Counter_Impl *m_impl;
};

template <class T>
struct CustomAllocator
{
    using value_type = T;

    CustomAllocator() = default;

    template <class U>
    constexpr CustomAllocator(const CustomAllocator<U> &other) noexcept
    {
        counter = other.counter;
    }

    T *allocate(std::size_t n)
    {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
        {
            throw std::bad_alloc();
        }
        const std::size_t bytes = n * sizeof(T);
        T *p = static_cast<T *>(std::malloc(bytes));
        if (p)
        {
            counter.increase(bytes);
            return p;
        }
        else
        {
            throw std::bad_alloc();
        }
    }

    void deallocate(T *p, std::size_t n) noexcept
    {
        std::free(p);

        const std::size_t bytes = n * sizeof(T);
        counter.decrease(bytes);
    }

    Byte_Counter counter;
};

static CustomAllocator<double> allocator;
size_t bytes()
{
    return allocator.counter.bytes();
}

size_t allocated()
{
    return allocator.counter.allocated();
}

size_t deallocated()
{
    return allocator.counter.deallocated();
}

class Matrix
{
private:
    std::vector<double, CustomAllocator<double>> m_array;
    size_t m_row_num, m_col_num;

public:
    Matrix(size_t row_num, size_t col_num) : m_array(allocator)
    {
        m_row_num = row_num;
        m_col_num = col_num;
        m_array.resize(row_num * col_num);
    }

    size_t nrow() const { return m_row_num; }
    size_t ncol() const { return m_col_num; }

    double *data()
    {
        return m_array.data();
    }

    double operator()(size_t row, size_t col) const
    {
        return m_array[row * m_col_num + col];
    }
    double &operator()(size_t row, size_t col)
    {
        return m_array[row * m_col_num + col];
    }

    double getitem(std::pair<size_t, size_t> index)
    {
        return (*this)(index.first, index.second);
    }

    void setitem(std::pair<size_t, size_t> index, double value)
    {
        (*this)(index.first, index.second) = value;
    }
};

/* bool operator==(Matrix const &mat1, Matrix const &mat2)
{
    if (mat1.ncol() != mat2.ncol() || mat1.nrow() != mat2.ncol())
        return false;

    for (size_t i = 0; i < mat1.nrow(); i++)
    {
        for (size_t j = 0; j < mat1.ncol(); j++)
        {
            if (mat1(i, j) != mat2(i, j))
                return false;
        }
    }
    return true;
} */