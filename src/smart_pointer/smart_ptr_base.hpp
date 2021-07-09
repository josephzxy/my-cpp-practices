#pragma once

template <typename T>
class smart_ptr
{
public:
    T* get() const noexcept;
    T& operator*() const noexcept;
    T* operator->() const noexcept;
    operator bool() const noexcept;

protected:
    smart_ptr(T* ptr = nullptr)
        : ptr_(ptr) {}
    // Resource release should be done in derived classes's destructor 
    virtual ~smart_ptr() {}
    T* ptr_;
};

#include "smart_ptr_base.ipp"
