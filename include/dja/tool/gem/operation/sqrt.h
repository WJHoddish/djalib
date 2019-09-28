#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_SQRT_
#define GEM_SQRT_

#include "../gem_conf.h"

#include "../judge/is_inf.h"
#include "../judge/is_nan.h"

#include "abs.h"

namespace gem {
// aux refers to auxiliary
namespace aux {
template <typename T>
constexpr T sqrt_recur(const T x, const T xn, const int count) noexcept {
  return (abs(xn - x / xn) / (T(1) + xn) < gem_lim<T>::epsilon() ?  // is
              xn  // if the residue is small enough
                                                                 :  // or
              count < GEM_MAX_ITER_SQRT ?                           // is
                  sqrt_recur(x, T(0.5) * (xn + x / xn), count + 1)
                                        :  // or
                  xn);
}

template <typename T>
constexpr T sqrt_check(const T x, const T val) noexcept {
  return (is_nan(x) ?  // is
              gem_lim<T>::quiet_NaN()
                    :                      // or
              x < T(0) ?                   // is
                  gem_lim<T>::quiet_NaN()  // by doing sqrt to negative numbers
                       :                   // or
                  is_pos_inf(x) ?          // is
                      x  // because the sqrt of infinite is still infinite
                                :  // or indistinguishable from zero or one
                      gem_lim<T>::epsilon() > abs(x) ?  // is
                          T(0)
                                                     :             // or
                          gem_lim<T>::epsilon() > abs(T(1) - x) ?  // is
                              x
                                                                :  // or
                              x > T(4) ?                           // is
                                  sqrt_check(x / T(4), T(2) * val)
                                       :  // or
                                  val * sqrt_recur(x, x / T(2), 0));
}
}  // namespace aux

/// \brief Solving square-root function at compile-time.
template <typename T>
constexpr return_t<T> sqrt(const T x) noexcept {
  return aux::sqrt_check(static_cast<return_t<T>>(x), return_t<T>(1));
}
}  // namespace gem

#endif
