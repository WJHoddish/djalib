// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a series of basic mathematical algorithms
//

#include "dja/math/math.h"

namespace dja {
	int gcd(int m, int n) {
		{
			m = std::abs(m);
			n = std::abs(n);
		}
		if (m < n) {
			std::swap(m, n);
		}
		return n == 0 ? m : gcd(n, m % n);
	}

	int lcm(int m, int n) {
		return (m * n / gcd(m, n));
	}

}