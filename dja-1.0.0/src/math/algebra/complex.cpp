// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a class to represent complex numbers.
//

#include "dja/math/complex.h"

namespace dja {
	Complex::Complex(double r, double i)
		:
		r_(r),
		i_(i) {}

	Complex::Complex(const Complex& src)
		:
		r_(src.r_),
		i_(src.i_) {}

	Complex& Complex::operator=(const Complex& src) {
		if (this != &src) {
			r_ = src.r_;
			i_ = src.i_;
		}
		return *this;
	}

	double Complex::modulus() const {
		return std::sqrt(r_ * r_ + i_ * i_);
	}

	bool Complex::operator==(const Complex& src) const {
		return (r_ == src.r_ && i_ == src.i_);
	}

	bool Complex::operator!=(const Complex& src) const {
		return (r_ != src.r_ || i_ != src.i_);
	}

	const Complex operator+(const Complex& m, const Complex& n) {
		return  Complex(m.r_ + n.r_, m.i_ + n.i_);
	}

	const Complex operator-(const Complex& m, const Complex& n) {
		return Complex(m.r_ - n.r_, m.i_ - n.i_);
	}

	const Complex operator*(const Complex& m, const Complex& n) {
		return Complex(m.r_ * n.r_ - m.i_ * n.i_, m.i_ * n.r_ + m.r_ * n.i_);
	}

	const Complex operator/(const Complex& m, const Complex& n) {
		double c = 1.0 / ((n.r_ * n.r_) + (n.i_ * n.i_));
		return Complex(c * ((m.r_ * n.r_) + (m.i_ * n.i_)), c * ((m.i_ * n.r_) - (m.r_ * n.i_)));
	}

	std::ostream& operator<<(std::ostream& os, const Complex& src) {
		src.display(os);
		return os;
	}

	void Complex::display(std::ostream& os) const {
		os << r_ << "+j" << i_;
	}
}