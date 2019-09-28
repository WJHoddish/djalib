#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_SIGN_
#define GEM_SIGN_

namespace gem {
/// \brief The sign function at compile-time.
template <typename T>
constexpr int sign(const T x) noexcept {
  return (x > T(0) ?      // is
              1           //  positive
                   :      // or
              x < T(0) ?  // is
                  -1      // negative
                       :  // or exactly equals to zero
                  0);
}
}  // namespace gem

#endif
