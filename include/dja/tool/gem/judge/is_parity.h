#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_PARITY_
#define GEM_PARITY_

#include "../gem_conf.h"

namespace gem {
namespace aux {
constexpr bool is_odd(const llint_t x) noexcept { return (x & 1U) != 0; }

constexpr bool is_even(const llint_t x) noexcept { return !is_odd(x); }
}  // namespace aux
}  // namespace gem

#endif