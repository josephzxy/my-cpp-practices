#pragma once
#include <utility>
#include "shared_ptr.hpp"

void shared_count::add_count() noexcept { this->count_++; }
size_t shared_count::reduce_count() noexcept { return --this->count_; }
size_t shared_count::get_count() const noexcept { return this->count_; }
