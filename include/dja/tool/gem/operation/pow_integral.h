#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_POW_INTEGRAL_
#define GEM_POW_INTEGRAL_

#include "../gem_conf.h"
#include "../gem_num.h"

#include "../judge/is_parity.h"

#include "num_part.h"  // find the fraction/whole number

namespace gem {
namespace aux {
template <typename T1, typename T2>
constexpr T1 pow_integral_compute(const T1 base, const T2 exp_term) noexcept;

/// \brief
///
/// \param
/// \param
/// \attention Exponentiation by squaring.
template <typename T1, typename T2>
constexpr T1 pow_integral_compute_recur(const T1 base, const T1 val,
                                        const T2 exp_term) noexcept {
  return (exp_term > T2(1) ?        // is
              ((is_odd(exp_term) ?  // is is_old() returns a bool value
                    pow_integral_compute_recur(base * base, val * base,
                                               exp_term / 2)
                                 :  // or
                    pow_integral_compute_recur(base * base, val,
                                               exp_term / 2)))
                           :        // or
              (exp_term == T2(1) ?  // is
                   val * base       // when exp_term <= 1
                                 :  // or
                   val));           // when exp_term < 1
}

/// \brief Case: type T2 is a signed type.
template <typename T1, typename T2,
          typename std::enable_if<std::is_signed<T2>::value>::type* = nullptr>
constexpr T1 pow_integral_sign_check(const T1 base,
                                     const T2 exp_term) noexcept {
  return (exp_term < T2(0) ?  // is
              T1(1) / pow_integral_compute(base, -exp_term)
                           :  // or
              pow_integral_compute_recur(base, T1(1), exp_term));
}

/// \brief Case: type T2 (exp_term) is NOT a signed type (e.g. size_t).
template <typename T1, typename T2,
          typename std::enable_if<!std::is_signed<T2>::value>::type* = nullptr>
constexpr T1 pow_integral_sign_check(const T1 base,
                                     const T2 exp_term) noexcept {
  return (pow_integral_compute_recur(base, T1(1), exp_term));
}

/// \brief
///
/// \param
/// \param
template <typename T1, typename T2>
constexpr T1 pow_integral_compute(const T1 base, const T2 exp_term) noexcept {
  return (exp_term == T2(3) ?              // is
              base * base * base           // special case: cube
                            :              // or
              exp_term == T2(2) ?          // is
                  base * base              // special case: square
                                :          // or
                  exp_term == T2(1) ?      // is
                      base                 // special case: n^1 == n
                                    :      // or
                      exp_term == T2(0) ?  // is
                          T1(1)            // special case: n^0 == 1
                                        :  // or
                                           // check for overflow
                          exp_term == gem_lim<T2>::min() ?  // is
                              T1(0)
                                                         :      // or
                              exp_term == gem_lim<T2>::max() ?  // is
                                  gem_lim<T1>::infinity()
                                                             :  // or
                                  pow_integral_sign_check(base, exp_term));
}

/// \brief Case: if exp_term is an integral type (not float, double...).
template <typename T1, typename T2,
          typename std::enable_if<std::is_integral<T2>::value>::type* = nullptr>
constexpr T1 pow_integral_type_check(const T1 base,
                                     const T2 exp_term) noexcept {
  return pow_integral_compute(base, exp_term);
}

/// \brief Case: if exp_term is NOT an integral type (e.g. float/double).
///
/// \brief This case should be treated carefully.
template <
    typename T1, typename T2,
    typename std::enable_if<!std::is_integral<T2>::value>::type* = nullptr>
constexpr T1 pow_integral_type_check(const T1 base,
                                     const T2 exp_term) noexcept {
  return pow_integral_compute(base, static_cast<llint_t>(exp_term));
}

template <typename T1, typename T2>
constexpr T1 pow_integral(const T1 base, const T2 exp_term) noexcept {
  return pow_integral_type_check(base, exp_term);
}
}  // namespace aux
}  // namespace gem

#endif
