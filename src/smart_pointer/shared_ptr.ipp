#pragma once
#include <utility>
#include "shared_ptr.hpp"

void shared_count::add_count() noexcept { this->count_++; }
size_t shared_count::reduce_count() noexcept { return --this->count_; }
size_t shared_count::get_count() const noexcept { return this->count_; }

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T> other) noexcept
{
    other.swap(*this);
    return *this;
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr<T>& other) noexcept
{
    std::swap(this->ptr_, other.ptr_);
    std::swap(this->shared_count_, other.shared_count_);
}

template <typename T>
size_t shared_ptr<T>::use_count() const
{
    if (this->ptr_)
    {
        return this->shared_count_->get_count();
    } else {
        return 0;
    }
}
