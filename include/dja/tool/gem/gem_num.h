#pragma once

// Copyright (C) 2019 Jiaheng Wang
// Author: Jiaheng Wang
// This file is a part of math section in the djalib.
//

#ifndef GEM_NUMERIC_H_
#define GEM_NUMERIC_H_

namespace gem {
// the maximum double value
const double dbl_max = 1.7976931348623158e+308;

// pi -- Pi
const long double pi = 3.1415926535897932384626433832795028841972L;

const long double half_pi = 1.5707963267948966192313216916397514420986L;

const long double sqrt_pi = 1.7724538509055160272981674833411451827975L;

// e  -- Euler's Constant
const double e = 2.7182818284590452354;

// sqrt_2 -- The square root of 2
const double sqrt_2 = 1.4142135623730950488;

// sqrt_3 -- The square root of 3
const double sqrt_3 = 1.7320508075688772935;

// lg_ -- The logarithm base 10 of _
const double lg_2 = 0.30102999566398119521;

// ln_ -- The logarithm base e of _
const long double ln_2 = 0.6931471805599453094172321214581765680755L;

const long double ln_10 = 2.3025850929940456840179914546843642076011L;

// light_spd -- The speed of light in vacuum in meters per second
const double spd_of_light = 2.99792458e8;

// golden_ratio -- The Golden Ratio
const double golden_ratio = 1.6180339887498948482;
}  // namespace gem

#endif