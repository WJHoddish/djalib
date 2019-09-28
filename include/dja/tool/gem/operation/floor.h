#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_FLOOR_
#define GEM_FLOOR_

#include "../gem_conf.h"

#include "../judge/is_inf.h"  // finite or infinite
#include "../judge/is_nan.h"
#include "../judge/sign.h"

#include "abs.h"

namespace gem {
namespace aux {
/// \brief
template <typename T>
constexpr int floor_resid(const T x, const T x_whole) noexcept {
  return ((x < T(0)) && (x < x_whole));
}

template <typename T>
constexpr T floor_int(const T x, const T x_whole) noexcept {
  return (x_whole - static_cast<T>(floor_resid(x, x_whole)));
}

template <typename T>
constexpr T floor_check(const T x) noexcept {
  return (is_nan(x) ?  // is
              gem_lim<T>::quiet_NaN()
                    :          // or
              !is_finite(x) ?  // is
                  x            // if x is +/- infinite
                            :  // or
                  gem_lim<T>::epsilon() > abs(x)
                      ?  // is
                      x  // if x approaches zero
                      :  // or (x is non-zero, and not a infinite number)
                      floor_int(x, T(static_cast<llint_t>(x))));
}
}  // namespace aux

/// \brief The floor function at compile-time.
template <typename T>
constexpr return_t<T> floor(const T x) noexcept {
  return aux::floor_check(static_cast<return_t<T>>(x));
}
}  // namespace gem

#endif
