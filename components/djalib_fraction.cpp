// definitions:
#include "fraction\djalib_fraction.h"

const djalib::Fraction djalib::Fraction::operator -() {
	return Fraction(
		-this->_up,
		this->_down);
}

const djalib::Fraction djalib::operator +(const Fraction& x, const Fraction& y) {
	int n = Fraction::lcm(x._down, y._down);
	return Fraction(
		n / x._down * x._up +
		n / y._down * y._up,
		n);
}

const djalib::Fraction djalib::operator -(const Fraction& x, const Fraction& y) {
	int n = Fraction::lcm(x._down, y._down);
	return Fraction(
		n / x._down * x._up -
		n / y._down * y._up,
		n);
}

const djalib::Fraction djalib::operator *(const Fraction& x, const Fraction& y) {
	return Fraction(
		x._up * y._up,
		x._down * y._down);
}

const djalib::Fraction djalib::operator /(const Fraction& x, const Fraction& y) {
	return Fraction(
		x._up * y._down,
		x._down * y._up);
}

//------------------------------
//------------------------------
bool djalib::operator ==(const Fraction& x, const Fraction& y) {
	return
		x.value() == y.value();
}

bool djalib::operator !=(const Fraction& x, const Fraction& y) {
	return
		!(x == y);
}

//------------------------------
//------------------------------
std::ostream& djalib::operator <<(std::ostream& os, const djalib::Fraction& fraction) {
	fraction.display(os);
	return os;
}
