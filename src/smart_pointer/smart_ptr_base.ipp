#pragma once
#include "smart_ptr_base.hpp"

template <typename T>
T* smart_ptr<T>::get() const { return this->ptr_; }

template <typename T>
T& smart_ptr<T>::operator*() const { return *ptr_; }

template <typename T>
T* smart_ptr<T>::operator->() const { return ptr_; }

template <typename T>
smart_ptr<T>::operator bool() const { return ptr_; }
