#include "_allocator.hpp"

//ByteCounterImpl
ByteCounter::ByteCounter(): m_impl(new ByteCounterImpl){ 
    incref();
}

ByteCounter::ByteCounter(ByteCounter const & other): m_impl(other.m_impl){ 
    incref(); 
}

ByteCounter & ByteCounter::operator=(ByteCounter const & other){
    if(&other != this){
        decref();
        m_impl = other.m_impl;
        incref();
    }
    return *this;
}

ByteCounter::ByteCounter(ByteCounter && other): m_impl(other.m_impl){ 
    incref(); 
}

ByteCounter & ByteCounter::operator=(ByteCounter && other){
    if (&other != this){
        decref();
        m_impl = other.m_impl;
        incref();
    }
    return *this;
}

ByteCounter::~ByteCounter(){ 
    decref(); 
}

void ByteCounter::swap(ByteCounter & other){
    std::swap(m_impl, other.m_impl);
}

void ByteCounter::increase(std::size_t amount){
    m_impl->allocated += amount;
}

void ByteCounter::decrease(std::size_t amount){
    m_impl->deallocated += amount;
}

std::size_t ByteCounter::bytes() const { 
    return m_impl->allocated - m_impl->deallocated; 
}

std::size_t ByteCounter::allocated() const { 
    return m_impl->allocated; 
}

std::size_t ByteCounter::deallocated() const { 
    return m_impl->deallocated; 
}

std::size_t ByteCounter::refcount() const { 
    return m_impl->refcount; 
}

void ByteCounter::incref() { 
    ++m_impl->refcount;
}
void ByteCounter::decref(){
    if (!m_impl){
        // Do nothing.
    }
    else if (1 == m_impl->refcount){
        delete m_impl;
        m_impl = nullptr;
    }
    else{
        --m_impl->refcount;
    }
}