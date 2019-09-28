#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_CONF_
#define GEM_CONF_

#include <limits>
#include <type_traits>

namespace gem {
using uint_t = unsigned int;

using llint_t = long long int;

using ullint_t = unsigned long long int;

template <class T>
using gem_lim = std::numeric_limits<T>;

/// \brief If the type T is an integral type, return_t becomes double.
/// If not (already been a float/double), just maintain.
template <typename T>
using return_t =
    typename std::conditional<std::is_integral<T>::value, double, T>::type;

/// \attention std::common_type<> obtains the common type for the types in the
/// types list to which all of them can be converted.
template <typename... T>
using common_t = typename std::common_type<T...>::type;

template <typename... T>
using common_return_t = return_t<common_t<T...>>;
}  // namespace gem

// convergence settings

#ifndef GEM_MAX_ITER_SQRT
#define GEM_MAX_ITER_SQRT 100
#endif

#ifndef GEM_MAX_ITER_EXP
#define GEM_MAX_ITER_EXP 25
#endif

#ifndef GEM_MAX_ITER_LOG
#define GEM_MAX_ITER_LOG 25
#endif

#endif