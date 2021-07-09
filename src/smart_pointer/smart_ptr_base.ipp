#pragma once
#include "smart_ptr_base.hpp"

template <typename T>
T* smart_ptr<T>::get() const noexcept { return this->ptr_; }

template <typename T>
T& smart_ptr<T>::operator*() const noexcept { return *ptr_; }

template <typename T>
T* smart_ptr<T>::operator->() const noexcept { return ptr_; }

template <typename T>
smart_ptr<T>::operator bool() const noexcept { return ptr_; }
