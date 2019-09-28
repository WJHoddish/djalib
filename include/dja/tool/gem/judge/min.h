#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_MIN_
#define GEM_MIN_

#include "../gem_conf.h"

namespace gem {
/// \brief The pairwise minimum function at compile-time.
///
/// \attention The recursive end.
template <typename T1, typename T2>
constexpr common_t<T1, T2> min(const T1 x, const T2 y) noexcept {
  return (x < y ? x : y);
}

template <typename T, typename... Ts>
constexpr common_t<T, Ts...> min(const T x, const Ts... y) noexcept {
  auto min_ = min(y...);
  return (x < min_ ? x : min_);
}
}  // namespace gem

#endif
