#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_LCM_
#define GEM_LCM_

#include "gcd.h"

namespace gem {
namespace aux {
template <typename T>
constexpr T lcm_compute(const T a, const T b) noexcept {
  return abs(a * (b / gcd(a, b)));
}

template <typename T1, typename T2, typename TC = common_t<T1, T2>>
constexpr TC lcm_type_check(const T1 a, const T2 b) noexcept {
  return lcm_compute(static_cast<TC>(a), static_cast<TC>(b));
}
}  // namespace aux

/// \brief The least common multiple (LCM) functionat at compile-time.
///
template <typename T1, typename T2>
constexpr common_t<T1, T2> lcm(const T1 a, const T2 b) noexcept {
  return aux::lcm_type_check(a, b);
}
}  // namespace gem

#endif