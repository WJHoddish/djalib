#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_NUM_PART_
#define GEM_NUM_PART_

#include "floor.h"

namespace gem {
namespace aux {
/// \return The return type is long long int.
template <typename T>
constexpr llint_t find_exponent(const T x, const llint_t exponent) noexcept {
  return (x < T(1) ?  // is
              find_exponent(x * T(10), exponent - llint_t(1))
                   :       // or
              x > T(10) ?  // is
                  find_exponent(x / T(10), exponent + llint_t(1))
                        :  // or
                  exponent);
}

/// \return The return type is long long int.
template <typename T>
constexpr llint_t find_whole(const T x) noexcept {
  return (abs(x - floor_check(x)) >= T(0.5) ?  // is
              static_cast<llint_t>(floor_check(x) + sign(x))
                                            :  // or
              static_cast<llint_t>(floor_check(x)));
}

template <typename T>
constexpr T find_fraction(const T x) noexcept {
  return (abs(x - floor_check(x)) >= T(0.5) ?  // is
              x - floor_check(x) - sign(x)
                                            :  // or
              x - floor_check(x));
}
}  // namespace aux
}  // namespace gem

#endif