#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_POW_
#define GEM_POW_

#include "exp.h"
#include "log.h"

namespace gem {
namespace aux {
/// \brief To deal with the situation when the exp_term is a decimal number.
template <typename T>
constexpr T pow_dbl(const T base, const T exp_term) noexcept {
  return exp(exp_term * log(base));
}

/// \brief Case: no decimal number.
template <typename T1, typename T2, typename TC = common_t<T1, T2>,
          typename std::enable_if<std::is_integral<T2>::value>::type* = nullptr>
constexpr TC pow_check(const T1 base, const T2 exp_term) noexcept {
  return pow_integral(base, exp_term);
}

/// \brief Case: exp_term is a decimal number.
template <
    typename T1, typename T2, typename TC = common_t<T1, T2>,
    typename std::enable_if<!std::is_integral<T2>::value>::type* = nullptr>
constexpr TC pow_check(const T1 base, const T2 exp_term) noexcept {
  return (base < T1(0) ?  // is
              gem_lim<TC>::quiet_NaN()
                       :  // or
              pow_dbl(static_cast<TC>(base), static_cast<TC>(exp_term)));
}
}  // namespace aux

template <typename T1, typename T2>
constexpr common_t<T1, T2> pow(const T1 base, const T2 exp_term) noexcept {
  return aux::pow_check(base, exp_term);
}
}  // namespace gem

#endif
