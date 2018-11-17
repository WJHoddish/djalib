#pragma once

#ifndef _FRACTION_H_
#define _FRACTION_H_

#include <cmath>
#include <cstdio>
#include <cassert>
#include <iostream>

namespace djalib
{
	class Fraction
	{
		int		_up;			// the numerator.
		int		_down;			// the denominator.

		static int gcd(int x, int y) {
			// the greatest common divisor (the Euclidean Algorithm).
			{
				x = std::abs(x);
				y = std::abs(y);
			}
			if (x < y)
				std::swap(x, y);
			return
				y == 0 ? x : gcd(y, x % y);
		}
		static int lcm(int x, int y) {
			// the least common multiple.
			int n =
				gcd(x, y);
			return
				(x * y / n);
		}
		void _simplify() {
			// simplify the object when constructing.
			{
				// make sure the denominator is positive!
				if (this->_down < 0) {
					this->_up = -(this->_up);
					this->_down = -(this->_down);
				}
			}
			{
				// reduction of a fraction.
				int n =
					gcd(this->_up, this->_down);
				this->_up /= n;
				this->_down /= n;
			}
		}

	public:
		Fraction(int up = 0, int down = 1) :
			_up(up), _down(down) {
			assert(this->_down != 0);
			_simplify();
			// 1. as only one number is given for constructing, the fraction is 'n/1' (=n).
			// 2. do simplification when constructing.
		}
		Fraction(const Fraction& ref) :
			_up(ref._up), _down(ref._down) {
			assert(this->_down != 0);
		}
		Fraction& operator =(const Fraction& ref) {
			if (this != &ref) {
				{
					this->_up = ref._up;
					this->_down = ref._down;
				}
				assert(this->_down != 0);
			}
			return *this;
		}

	public:
		double value() const {
			return
				(double)this->_up /
				(double)this->_down;
		}
		Fraction reciprocal() const {
			return
				1 / (*this);
		}

	public:
		friend std::ostream& operator <<(std::ostream& os, const djalib::Fraction& fraction);

		friend const Fraction operator +(const Fraction& x, const Fraction& y);	// arithmetic: +;
		friend const Fraction operator -(const Fraction& x, const Fraction& y);	// arithmetic: -;
		friend const Fraction operator *(const Fraction& x, const Fraction& y);	// arithmetic: *;
		friend const Fraction operator /(const Fraction& x, const Fraction& y);	// arithmetic: /.

		friend bool operator ==(const Fraction& x, const Fraction& y);
		friend bool operator !=(const Fraction& x, const Fraction& y);

		const Fraction operator -();	// the minus sign.

	protected:
		void display(std::ostream& os) const {
			os <<
				this->_up << " / " << this->_down;
		}
	};

}

#endif
