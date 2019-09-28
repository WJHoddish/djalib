#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_TAN_
#define GEM_TAN_

#include "../operation/pow_integral.h"

namespace gem {
namespace aux {
/// \brief
template <typename T>
constexpr T tan_series_exp_long(
    const T z) noexcept {  // this is based on a fourth-order expansion of
                           // tan(z) using Bernoulli numbers
  return (-1 / z +
          (z / 3 + (pow_integral(z, 3) / 45 + (2 * pow_integral(z, 5) / 945 +
                                               pow_integral(z, 7) / 4725))));
}

template <typename T>
constexpr T tan_series_exp(const T x) noexcept {
  return (
      gem_lim<T>::epsilon() > abs(x - T(gem::half_pi))
          ?  // is
          T(1.633124e+16)
          // the value tan(pi/2) is somewhat of a convention;
          // technically the function is not defined at EXACTLY pi/2,
          // but this is floating point pi/2
          :  // or
          tan_series_exp_long(
              x -
              T(gem::half_pi)));  // otherwise we use an expansion around pi/2
}

template <typename T>
constexpr T tan_cf_recur(const T xx, const int depth,
                         const int max_depth) noexcept {
  return (depth < max_depth ?  // is
              T(2 * depth - 1) - xx / tan_cf_recur(xx, depth + 1, max_depth)
                            :  // or
              T(2 * depth - 1));
}

template <typename T>
constexpr T tan_cf_main(const T x) noexcept {
  return ((x > T(1.55) && x < T(1.60)) ?  // is
              tan_series_exp(x)  // deals with a singularity at tan(pi/2)
                                       :  // or
              x > T(1.4) ?                // is
                  (x / tan_cf_recur(x * x, 1, 45))
                         :     // or
                  (x > T(1) ?  // is
                       x / tan_cf_recur(x * x, 1, 35)
                            :  // or
                       x / tan_cf_recur(x * x, 1, 25)));
}

template <typename T>
constexpr T tan_begin(const T x, const int count = 0) noexcept {
  // tan(x) = tan(x + pi)
  return (
      x > T(gem::pi) ?  // is
          count > 1 ?   // is
              gem_lim<T>::quiet_NaN()
                    :  // or
                       // protect against undefined behavior
              tan_begin(x - T(gem::pi) * floor_check(x / T(gem::pi)), count + 1)
                     :  // or
          tan_cf_main(x));
}

template <typename T>
constexpr T tan_check(const T x) noexcept {
  return (is_nan(x) ?  // is
              gem_lim<T>::quiet_NaN()
                    :                           // or
              gem_lim<T>::epsilon() > abs(x) ?  // is
                  T(0)                          // x ~= 0
                                             :  // or
                  x < T(0) ?                    // is
                      -tan_begin(-x)
                           :  // or
                      tan_begin(x));
}
}  // namespace aux

/// \brief The tangent function at compile-time.
template <typename T>
constexpr return_t<T> tan(const T x) noexcept {
  return aux::tan_check(static_cast<return_t<T>>(x));
}
}  // namespace gem

#endif
