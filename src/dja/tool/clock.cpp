#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// Output the system time.
//

#include "clock.h"

namespace dja {
Clock::Clock() { init(); }

std::string Clock::date() {
  std::string y, m, d;
  {
    y = std::to_string(ltm.tm_year + 1900);
    m = std::to_string(ltm.tm_mon + 1);
    d = std::to_string(ltm.tm_mday);
  }
  return y + "_" + m + "_" + d;
}

std::string Clock::clock() {
  std::string h, m, s;
  {
    h = std::to_string(ltm.tm_hour);
    m = std::to_string(ltm.tm_min);
    s = std::to_string(ltm.tm_sec);
  }
  return h + "_" + m + "_" + s;
}

bool Clock::init() {
  // derive the system date and time
  std::time(&now);
  // derive the local time
  return localtime_s(&ltm, &now);
}
}  // namespace dja