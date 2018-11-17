// definitions:
#include "mutual\djalib_complex.h"

djalib::Complexnum djalib::operator +(const Complexnum& m, const Complexnum& n) {
	return Complexnum(
		m._r + n._r, 
		m._i + n._i);
}
djalib::Complexnum djalib::operator -(const Complexnum& m, const Complexnum& n) {
	return Complexnum(
		m._r - n._r, 
		m._i - n._i);
}
djalib::Complexnum djalib::operator *(const Complexnum& m, const Complexnum& n) {
	return Complexnum(
		m._r * n._r - m._i * n._i, 
		m._i * n._r + m._r * n._i);
}
djalib::Complexnum djalib::operator /(const Complexnum& m, const Complexnum& n) {
	assert(n.abs() > 0);
	double nem = 
		(n._r * n._r) + (n._i * n._i);
	return Complexnum(
		((m._r * n._r) + (m._i * n._i)) / nem, 
		((m._i * n._r) - (m._r * n._i)) / nem);
}

//------------------------------
//------------------------------
std::ostream& djalib::operator <<(std::ostream& os, const djalib::Complexnum& complex) {
	return os << complex.toString();
}
