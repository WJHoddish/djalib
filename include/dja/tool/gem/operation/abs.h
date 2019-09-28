#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_ABS_
#define GEM_ABS_

namespace gem {
/// \brief Obtain the absolute value of the input.
///
/// \attention The word "constexpr" refers to the "constant expression".
/// A kind of expression that can be specified during the compilation time (e.g.
/// the result of using the sizeof()).
template <typename T>
constexpr T abs(const T x) noexcept {
  // deal with signed-zeros
  return (x == T(0) ?
                    // is
              T(0)
                    :
                    // or
              x < T(0) ?
                       // is
                  -x
                       :
                       // or
                  x);
}
}  // namespace gem

#endif
