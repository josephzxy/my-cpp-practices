#pragma once
#include "smart_ptr_base.hpp"

template <typename T> class unique_ptr : public smart_ptr<T> {
    /*
    unique_ptr fully utilises RAII and will free the resources
    on its destruction(e.g. when it reaches the end of the scope)
    It's important that at any time there should be ONLY one unique_ptr
    for a piece of resource on the heap or it may result in releasing
    the same chunk of memory multiple times.
    */
public:
    explicit unique_ptr(T* ptr = nullptr)
        : smart_ptr<T>(ptr)
    {
    }

    // the copy constructor will be marked as delete
    // implicitly if the move constructor is presented.
    // It does no harm to explicitly mark it as delete here.
    unique_ptr(unique_ptr& other) = delete;
    // It's a common practice to keep both the template
    // and the non-template version
    template <typename U> unique_ptr<T>(unique_ptr<U>&& other)
    {
        this->ptr_ = other.release();
    }

    unique_ptr(unique_ptr<T>&& other) { this->ptr_ = other.release(); }

    ~unique_ptr() { delete this->ptr_; }

    unique_ptr<T>& operator=(unique_ptr<T> other);

    T* release() noexcept;

    void swap(unique_ptr<T>& other) noexcept;
};

#include "unique_ptr.ipp"
