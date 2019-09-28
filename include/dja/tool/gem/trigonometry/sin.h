#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_SIN_
#define GEM_SIN_

#include "tan.h"

namespace gem {
namespace aux {
template <typename T>
constexpr T sin_compute(const T x) noexcept {
  return T(2) * x / (T(1) + x * x);
}

template <typename T>
constexpr T sin_check(const T x) noexcept {
  return (is_nan(x) ?                  // is
              gem_lim<T>::quiet_NaN()  // because the input isn't a value
                    :                  // or
              gem_lim<T>::epsilon() > abs(x) ?                   // is
                  T(0)                                           // x ~= 0
                                             :                   // or
                  gem_lim<T>::epsilon() > abs(x - T(half_pi)) ?  // is
                      T(1)                                       // x ~= pi/2
                                                              :  // or
                      gem_lim<T>::epsilon() > abs(x + T(half_pi)) ?  // is
                          -T(1)  // x ~= -pi/2
                                                                  :  // or
                          gem_lim<T>::epsilon() > abs(x - T(pi)) ?   // is
                              T(0)                                   // x ~= pi
                                                                 :   // or
                              gem_lim<T>::epsilon() > abs(x + T(pi)) ?  // is
                                  -T(0)  // x ~= -pi
                                                                     :  // or
                                  sin_compute(tan(x / T(2))));
}
}  // namespace aux

/// \brief The sine function at compile-time.
template <typename T>
constexpr return_t<T> sin(const T x) noexcept {
  return aux::sin_check(static_cast<return_t<T>>(x));
}
}  // namespace gem

#endif