#pragma once
#include <utility>
#include "shared_ptr.hpp"

void shared_count::add_count() { this->count_++; }
size_t shared_count::reduce_count() { return --this->count_; }
size_t shared_count::get_count() const { return this->count_; }
