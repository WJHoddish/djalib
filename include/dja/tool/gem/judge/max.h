#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_MAX_
#define GEM_MAX_

#include "../gem_conf.h"

namespace gem {
/// \brief The pairwise maximum function at compile-time.
///
/// \attention The recursive end.
template <typename T1, typename T2>
constexpr common_t<T1, T2> max(const T1 x, const T2 y) noexcept {
  return (x > y ? x : y);
}

template <typename T, typename... Ts>
constexpr common_t<T, Ts...> max(const T x, const Ts... y) noexcept {
  auto max_ = max(y...);
  return (x > max_ ? x : max_);
}
}  // namespace gem

#endif
