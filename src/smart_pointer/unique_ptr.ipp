#pragma once
#include "unique_ptr.hpp"
#include <utility>

template<typename T>
unique_ptr<T>&
unique_ptr<T>::operator=(unique_ptr<T> other)
{
    /*
    Note that we are taking value instead of reference
    in the argument list so as to create a temporary
    local variable either by move or copy,

    swap is noexcept. The only place where errors may occur
    is contructing the new temporary object.
    The advantage of this practice is that "this" won't get
    affected if constructing the new temporary object fails.
    */
    other.swap(*this);
    return *this;
}

template<typename T>
T*
unique_ptr<T>::release() noexcept
{
    T* p = this->ptr_;
    this->ptr_ = nullptr;
    return p;
}

template<typename T>
void
unique_ptr<T>::swap(unique_ptr<T>& other) noexcept
{
    std::swap(this->ptr_, other.ptr_);
}
