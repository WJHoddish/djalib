#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_EXP_
#define GEM_EXP_

#include "pow_integral.h"

namespace gem {
namespace aux {
template <typename T>
constexpr T exp_cf_recur(const T x, const int depth) noexcept {
  return (depth < GEM_MAX_ITER_EXP ?  // is *
              (depth == 1 ?           // is
                   (T(1) - x / exp_cf_recur(x, depth + 1))
                          :  // or
                   (T(1) + x / (T(depth) - T(1)) -
                    x / depth / exp_cf_recur(x, depth + 1)))
                                   :  // or *
              T(1));
}

/// \brief Compute exp (when the exp_term < 2).
template <typename T>
constexpr T exp_cf(const T x) noexcept {
  return (T(1) / exp_cf_recur(x, 1));
}

/// \brief Compute exp (when the exp_term >= 2).
template <typename T>
constexpr T exp_split(const T x) noexcept {
  return (pow_integral(gem::e, find_whole(x)) * exp_cf(find_fraction(x)));
}

template <typename T>
constexpr T exp_check(const T x) noexcept {
  return (is_nan(x) ?  // is
              gem_lim<T>::quiet_NaN()
                    :          // or
              is_neg_inf(x) ?  // is
                  T(0)
                            :                       // or
                  gem_lim<T>::epsilon() > abs(x) ?  // is
                      T(1)
                                                 :  // or
                      is_pos_inf(x) ?               // is
                          gem_lim<T>::infinity()    // because the input
                                                    // approaches infinity
                                    :  // or (not nan, neg/pos infinity or ~ 0)
                          abs(x) < T(2) ?  // is
                              exp_cf(x)
                                        :  // or
                              exp_split(x));
}
}  // namespace aux

/// \brief The exponential function at compile-time.
///
/// \attention e^x.
template <typename T>
constexpr return_t<T> exp(const T x) noexcept {
  return aux::exp_check(static_cast<return_t<T>>(x));
}
}  // namespace gem

#endif
