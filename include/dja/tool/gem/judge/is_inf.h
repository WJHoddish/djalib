#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_IS_INF_
#define GEM_IS_INF_

#include "../gem_conf.h"

#include "is_nan.h"

namespace gem {
namespace aux {
// infinite

template <typename T>
constexpr bool is_neg_inf(const T x) noexcept {
  return x == -gem_lim<T>::infinity();
}

template <typename T>
constexpr bool is_pos_inf(const T x) noexcept {
  return x == gem_lim<T>::infinity();
}

/// \brief The recursive end.
template <typename T>
constexpr bool any_neg_inf(const T x) noexcept {
  return is_neg_inf(x);
}

template <typename T, typename... Ts>
constexpr bool any_neg_inf(const T x, const Ts... y) noexcept {
  return any_neg_inf(x) || any_neg_inf(y...);
}

/// \brief The recursive end.
template <typename T>
constexpr bool any_pos_inf(const T x) noexcept {
  return is_pos_inf(x);
}

template <typename T, typename... Ts>
constexpr bool any_pos_inf(const T x, const Ts... y) noexcept {
  return any_pos_inf(x) || any_pos_inf(y...);
}

/// \brief
template <typename T>
constexpr bool is_inf(const T x) noexcept {
  return (is_neg_inf(x) || is_pos_inf(x));
}

// finite

template <typename T>
constexpr bool is_finite(const T x) noexcept {
  return (!is_nan(x)) && (!is_inf(x));
}
}  // namespace aux
}  // namespace gem

#endif