#pragma once
#ifndef _COMPLEX_NUM_H_
#define _COMPLEX_NUM_H_

#include <iostream>
#include "djalib_text.h"

namespace djalib
{
	class Complexnum
	{
		double		_r;			// the real part.
		double		_i;			// the imaginary part.

	public:
		Complexnum(double r = 0.0, double i = 0.0) :
			_r(r), _i(i) {
			// 1. as only one number is given for constructing, im part has a default value: 0.
		}
		Complexnum(const Complexnum& complex) :
			_r(complex.getReal()), _i(complex.getImag()) {
		}
		Complexnum& operator =(const Complexnum& ref_num) {
			if (this != &ref_num) {
				this->_r = ref_num._r;
				this->_i = ref_num._i;
			}
			return 
				*this;
		}

	public:
		double abs() const {
			return std::sqrt(_r * _r + _i * _i);
		}
		double getReal() const {
			return _r;
		}
		double getImag() const {
			return _i;
		}

		std::string toString() const {
			return
				djalib::doubleToString(_r) +
				" + " +
				djalib::doubleToString(_i) +
				"i";
		}

	public:
		bool operator ==(const Complexnum& c2) const {
			return
				(_r == c2._r) &&
				(_i == c2._i);
		}
		bool operator !=(const Complexnum& c2) const {
			return
				(_r != c2._r) ||
				(_i != c2._i);
		}

	public:
		friend std::ostream& operator <<(std::ostream& os, const djalib::Complexnum& complex);

		friend Complexnum operator +(const Complexnum& m, const Complexnum& n);
		friend Complexnum operator -(const Complexnum& m, const Complexnum& n);
		friend Complexnum operator *(const Complexnum& m, const Complexnum& n);
		friend Complexnum operator /(const Complexnum& m, const Complexnum& n);

	};

}

#endif
