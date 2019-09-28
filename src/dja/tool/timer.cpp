// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a timer.
//

#include "timer.h"

namespace dja {
Timer::Timer() : begin_(std::chrono::high_resolution_clock::now()) {}

bool Timer::reset() { begin_ = std::chrono::high_resolution_clock::now(); }

long long Timer::elapsed() const {
  using namespace std::chrono;
  return duration_cast<milliseconds>(time_unit::now() - begin_).count();
}
}  // namespace dja