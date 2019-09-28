#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a timer.
//

#ifndef DJA_TIMER_H_
#define DJA_TIMER_H_

#include <chrono>
#include <iostream>

namespace dja {
/// \brief A cpp timer implementation.
class Timer {
 public:
  /// \brief The constructor.
  Timer();

  /// \brief Reset the timer.
  bool reset();

  /// \brief Compute the total time elapsed.
  long long elapsed() const;

 private:
  typedef std::chrono::high_resolution_clock time_unit;

  ///< \brief the point start ticking
  std::chrono::time_point<time_unit> begin_;
};
}  // namespace dja

#endif  // DJA_TIMER_H_