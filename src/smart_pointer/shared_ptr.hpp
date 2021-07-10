#pragma once
#include "smart_ptr_base.hpp"
#include <cstddef>

class shared_count
{
  public:
    shared_count () noexcept : count_ (1) {}

    void add_count () noexcept;
    size_t reduce_count () noexcept;
    size_t get_count () const noexcept;

  private:
    size_t count_;
};

template <typename T> class shared_ptr : public smart_ptr<T>
{
  public:
    explicit shared_ptr (T* ptr = nullptr) : shared_count_ (nullptr)
    {
        this->ptr_ = ptr;
        if (ptr)
            {
                this->shared_count_ = new shared_count ();
            }
    }
    ~shared_ptr () override
    {
        if (this->ptr_ && this->shared_count_->reduce_count () == 0)
            {
                delete this->ptr_;
                delete this->shared_count_;
            }
    }

    shared_ptr (const shared_ptr<T>& other) noexcept
    {
        this->ptr_ = other.ptr_;

        if (!this->ptr_)
            return;
        this->shared_count_ = other.shared_count_;
        this->shared_count_->add_count ();
    }

    template <typename U> shared_ptr (const shared_ptr<U>& other) noexcept
    {
        // TODO: need to ensure type U is the
        // derived type from T
        this->ptr_ = other.ptr_;

        if (!this->ptr_)
            return;
        this->shared_count_ = other.shared_count_;
        this->shared_count_->add_count ();
    }

    shared_ptr (shared_ptr<T>&& other) noexcept
    {
        this->ptr_ = other.ptr_;
        if (!this->ptr_)
            return;

        this->shared_count_ = other.shared_count_;
        other.ptr_ = nullptr;
        other.shared_count_ = nullptr;
    }

    template <typename U> shared_ptr (shared_ptr<U>&& other) noexcept
    {
        this->ptr_ = other.ptr_;
        if (!this->ptr_)
            return;

        this->shared_count_ = other.shared_count_;
        other.ptr_ = nullptr;
        other.shared_count_ = nullptr;
    }

    template <typename U>
    shared_ptr (const shared_ptr<U>& other, T* ptr) noexcept
    {
        this->ptr_ = ptr;
        if (!this->ptr_)
            {
                return;
            }
        other.shared_count_->add_count ();
        this->shared_count_ = other.shared_count_;
    }

    shared_ptr<T>& operator= (shared_ptr<T> other) noexcept;

    void swap (shared_ptr<T>& other) noexcept;

    size_t use_count () const;

    template <typename U> friend class shared_ptr;

  private:
    shared_count* shared_count_;
};

template <typename T, typename U>
shared_ptr<T>
dynamic_pointer_cast (const shared_ptr<U>& other)
{
    T* ptr = dynamic_cast<T*> (other.get ());
    return shared_ptr<T> (other, ptr);
}

#include "shared_ptr.ipp"
