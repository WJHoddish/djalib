#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_NUM_MANTISSA_
#define GEM_NUM_MANTISSA_

namespace gem {
namespace aux {
template <typename T>
constexpr T mantissa(const T x) noexcept {
  return (x < T(1) ?  // is
              mantissa(x * T(10))
                   :       // or
              x > T(10) ?  // is
                  mantissa(x / T(10))
                        :  // or
                  x);
}
}  // namespace aux
}  // namespace gem

#endif
