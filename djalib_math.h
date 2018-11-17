#pragma once

#ifndef _MATHEMATICS_h_
#define _MATHEMATICS_h_

#include <vector>
#include <iostream>

namespace djalib
{
	// macro definitions:
#define djaPi       3.14159265358979323846   // pi
#define djaPi_2     1.57079632679489661923   // pi / 2
#define djaPi_4     0.785398163397448309616  // pi / 4

	// average of numbers recorded in a std::vector.
	template <typename T>
	double Average(std::vector<T>& vec);

	// power.
	double Power(double base, size_t pow = 2);

	// square.,m
	double Sqrt(double pow);
}

double djalib::Power(double base, size_t pow) {
	double result 
		= 1;
	while (pow) {
		if (pow & 1)
			result *= base;
		pow >>= 1;
		base *= base;
	}
	return 
		result;
}

double djalib::Sqrt(double pow) {
	// Gauss-Newton iteration method:
	// a + b >= 2 * sqrt(a * b)!
	double x1 
		= pow + 0.25, x0;
	do {
		x0 = x1;
		x1 = (x0 * x0 + pow) / (2 * x0);
	} while (std::fabs(x1 - x0) > 0.5E-05);
	return 
		x1;
}

template <typename T>
double djalib::Average(std::vector<T>& vec) {
	double avg = 0;
	for (size_t idx = 0; idx < vec.size(); ++idx) {
		avg += (vec[idx] - avg) / (idx + 1);
	}
	return avg;
}

#endif
