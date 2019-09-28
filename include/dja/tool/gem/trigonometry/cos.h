#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_COS_
#define GEM_COS_

#include "tan.h"

namespace gem {
namespace aux {
template <typename T>
constexpr T cos_compute(const T x) noexcept {
  return (T(1) - x * x) / (T(1) + x * x);
}

template <typename T>
constexpr T cos_check(const T x) noexcept {
  return (is_nan(x) ?  // is
              gem_lim<T>::quiet_NaN()
                    :                           // or
              gem_lim<T>::epsilon() > abs(x) ?  // is
                  T(1)
                                             :                   // or
                  gem_lim<T>::epsilon() > abs(x - T(half_pi)) ?  // is
                      T(0)
                                                              :      // or
                      gem_lim<T>::epsilon() > abs(x + T(half_pi)) ?  // is
                          T(0)
                                                                  :  // or
                          gem_lim<T>::epsilon() > abs(x - T(pi)) ?   // is
                              -T(1)
                                                                 :      // or
                              gem_lim<T>::epsilon() > abs(x + T(pi)) ?  // is
                                  -T(1)
                                                                     :  // or
                                  cos_compute(tan(x / T(2))));
}
}  // namespace aux

/// \brief The cosine function at compile-time.
template <typename T>
constexpr return_t<T> cos(const T x) noexcept {
  return aux::cos_check(static_cast<return_t<T>>(x));
}
}  // namespace gem

#endif
