// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a class to represent fraction numbers.
//

#include "dja/math/fraction.h"

namespace dja {
	Fraction::Fraction(int n, int d)
		:
		n_(n),
		d_(d) {
		simplify();
	}

	Fraction::Fraction(const Fraction& src)
		:
		n_(src.n_),
		d_(src.d_) {}

	Fraction& Fraction::operator=(const Fraction& src) {
		if (this != &src) {
			n_ = src.n_;
			d_ = src.d_;
		}
		return *this;
	}

	double Fraction::value() const {
		return static_cast<double>(n_) / static_cast<double>(d_);
	}

	Fraction Fraction::reciprocal() const {
		return 1 / (*this);
	}

	const Fraction Fraction::operator-() {
		return Fraction(n_ * (-1), d_);
	}

	bool operator==(const Fraction& m, const Fraction& n) {
		return (m.value() == n.value());
	}

	bool operator!=(const Fraction& m, const Fraction& n) {
		return !(m == n);
	}

	const Fraction operator+(const Fraction& m, const Fraction& n) {
		int c = lcm(m.d_, n.d_);
		return Fraction(c / m.d_ * m.n_ + c / n.d_ * n.n_, c);
	}

	const Fraction operator-(const Fraction& m, const Fraction& n) {
		int c = lcm(m.d_, n.d_);
		return Fraction(c / m.d_ * m.n_ - c / n.d_ * n.n_, c);
	}

	const Fraction operator*(const Fraction& m, const Fraction& n) {
		return Fraction(m.n_ * n.n_, m.d_ * n.d_);
	}

	const Fraction operator/(const Fraction& m, const Fraction& n) {
		return Fraction(m.n_ * n.d_, m.d_ * n.n_);
	}

	std::ostream& operator<<(std::ostream& os, const Fraction& src) {
		src.display(os);
		return os;
	}

	void Fraction::display(std::ostream& os) const {
		os << n_ << "/" << d_;
	}

	void Fraction::simplify() {
		// ensure the denominator is positive
		if (d_ < 0) {
			n_ *= -1;
			d_ *= -1;
		}
		// the reduction of a fraction
		int c = gcd(n_, d_);
		n_ /= c;
		d_ /= c;
	}
}
