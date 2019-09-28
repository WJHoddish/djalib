#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_LOG_
#define GEM_LOG_

#include "../gem_conf.h"
#include "../gem_num.h"

#include "num_mantissa.h"
#include "num_part.h"

namespace gem {
namespace aux {
template <typename T>
constexpr T log_cf_main(const T xx, const int depth) noexcept {
  return (depth < GEM_MAX_ITER_LOG ?  // is
              T(2 * depth - 1) -
                  T(depth * depth) * xx / log_cf_main(xx, depth + 1)
                                   :  // or
              T(2 * depth - 1));
}

template <typename T>
constexpr T log_cf_begin(const T x) noexcept {
  return (T(2) * x / log_cf_main(x * x, 1));
}

template <typename T>
constexpr T log_main(const T x) noexcept {
  return log_cf_begin((x - T(1)) / (x + T(1)));
}

constexpr long double log_mantissa_integer(const int x) noexcept {
  switch (x) {
    case 2: {
      return 0.6931471805599453094172321214581765680755L;
    }
    case 3: {
      return 1.0986122886681096913952452369225257046475L;
    }
    case 4: {
      return 1.3862943611198906188344642429163531361510L;
    }
    case 5: {
      return 1.6094379124341003746007593332261876395256L;
    }
    case 6: {
      return 1.7917594692280550008124773583807022727230L;
    }
    case 7: {
      return 1.9459101490553133051053527434431797296371L;
    }
    case 8: {
      return 2.0794415416798359282516963643745297042265L;
    }
    case 9: {
      return 2.1972245773362193827904904738450514092950L;
    }
    case 10: {
      return 2.3025850929940456840179914546843642076011L;
    }
    default: {
      break;
    }
  }
  return 0.0L;
}

template <typename T>
constexpr T log_mantissa(const T x) noexcept {
  // divide by the integer part of x, which will be in
  // [1, 10], then adjust using tables
  return (log_main(x / T(static_cast<int>(x))) +
          T(log_mantissa_integer(static_cast<int>(x))));
}

template <typename T>
constexpr T log_breakup(const T x) noexcept {  // x = a*b, where b = 10^c
  return (log_mantissa(mantissa(x)) + T(ln_10) * T(find_exponent(x, 0)));
}

template <typename T>
constexpr T log_check(const T x) noexcept {
  return (is_nan(x) ?  // is
              gem_lim<T>::quiet_NaN()
                    :                      // or
              x < T(0) ?                   // is
                  gem_lim<T>::quiet_NaN()  // log() do not accept minus number
                       :                   // or
                  gem_lim<T>::epsilon() > x ?                  // is
                      -gem_lim<T>::infinity()                  // x ~= 0
                                            :                  // or
                      gem_lim<T>::epsilon() > abs(x - T(1)) ?  // is
                          T(0)                                 // x ~= 1
                                                            :  // or
                          x == gem_lim<T>::infinity() ?        // is pos inf
                              gem_lim<T>::infinity()        // log(inf) == inf
                                                      :     // or
                              (x < T(0.5) || x > T(1.5)) ?  // is *
                                  log_breakup(x)
                                                         :  // or *
                                  log_main(x));
}
}  // namespace aux

/// \brief The natural logarithm function at compile-time.
template <typename T>
constexpr return_t<T> log(const T x) noexcept {
  return aux::log_check(static_cast<return_t<T>>(x));
}
}  // namespace gem

#endif
