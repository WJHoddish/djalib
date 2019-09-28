#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_GCD_
#define GEM_GCD_

#include "../gem_conf.h"

#include "abs.h"

namespace gem {
namespace aux {
template <typename T>
constexpr T gcd_compute(const T a, const T b) noexcept {
  return (
      b == T(0) ?  // is
          a  // return the value of the first input if the second one is zero
                :  // or
          gcd_compute(b, a % b));
}

// \brief Case: type T is bool, char, char16_t, char32_t, wchar_t, short, int,
// long or long long.
template <typename T,
          typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
constexpr T gcd_int_check(const T a, const T b) noexcept {
  return gcd_compute(a, b);
}

// \brief Case: type T does not represent a integral type (cannot be converted
// as an integer).
template <typename T,
          typename std::enable_if<!std::is_integral<T>::value>::type* = nullptr>
constexpr T gcd_int_check(const T a, const T b) noexcept {
  // convert into the "unsigned long long int"
  return gcd_recur(static_cast<ullint_t>(a), static_cast<ullint_t>(b));
}

template <typename T1, typename T2, typename TC = common_t<T1, T2>>
constexpr TC gcd_type_check(const T1 a, const T2 b) noexcept {
  return gcd_int_check(static_cast<TC>(abs(a)), static_cast<TC>(abs(b)));
}
}  // namespace aux

/// \brief The greatest common divisor (GCD) function at compile-time.
///
/// \param a integral-valued input.
/// \param b integral-valued input.
template <typename T1, typename T2>
constexpr common_t<T1, T2> gcd(const T1 a, const T2 b) noexcept {
  return aux::gcd_type_check(a, b);
}
}  // namespace gem

#endif