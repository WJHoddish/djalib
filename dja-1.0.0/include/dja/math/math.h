#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a series of basic mathematical algorithms
//

#ifndef DJA_MATH_H_
#define DJA_MATH_H_

#include <iostream>
#include <cstdio>
#include <cmath>

#include "dja/math/numeric.h"

namespace dja {
	/// \brief Use the Euclidean algorithm to solve the greatest common divisor.
	int gcd(int m, int n);

	/// \brief Solve the least common multiple.
	int lcm(int m, int n);

}

#endif	// DJA_MATH_H_