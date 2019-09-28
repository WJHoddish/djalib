#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// Output the system time.
//

#ifndef DJA_BEN_H_
#define DJA_BEN_H_

#include <ctime>
#include <string>

namespace dja {
/// \brief A cpp timer implementation.
class Clock {
 public:
  /// \brief The constructor.
  Clock();

  /// \brief Get year, month and day.
  std::string date();

  /// \brief Get hour, minute and second.
  std::string clock();

 private:
  bool init();

  tm ltm;
  time_t now;
};
}  // namespace dja

#endif