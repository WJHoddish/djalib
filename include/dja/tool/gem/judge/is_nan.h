#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_IS_NAN_
#define GEM_IS_NAN_

namespace gem {
/// \brief
template <typename T>
constexpr bool is_nan(const T x) noexcept {
  return (x != x);
}

/// \brief The recursive end.
template <typename T>
constexpr bool any_nan(const T x) noexcept {
  return is_nan(x);
}

template <typename T, typename... Ts>
constexpr bool any_nan(const T x, const Ts... y) noexcept {
  return (any_nan(x) || any_nan(y...));
}
}  // namespace gem

#endif