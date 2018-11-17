// definitions:
#include "mutual\djalib_roman.h"

const djalib::tinystr djalib::Roman::B[10] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
const djalib::tinystr djalib::Roman::T[10] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
const djalib::tinystr djalib::Roman::H[10] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
const djalib::tinystr djalib::Roman::K[4] = { "", "M", "MM", "MMM" };

djalib::Roman djalib::operator +(const Roman& m, const Roman& n) {
	assert(m._arb + n._arb <= 3999);
	return 
		Roman(m._arb + n._arb);
}

djalib::Roman djalib::operator -(const Roman& m, const Roman& n) {
	assert(m._arb > n._arb);
	return
		Roman(m._arb - n._arb);
}

// comparison.
bool djalib::operator ==(const Roman& m, const Roman& n) {
	return
		m._arb == n._arb;
}

bool djalib::Roman::operator >(const Roman& ref) {
	return
		this->_arb > ref._arb;
}

bool djalib::Roman::operator <(const Roman& ref) {
	return
		this->_arb < ref._arb;
}

//------------------------------
//------------------------------
std::ostream& djalib::operator <<(std::ostream& os, const Roman& rom) {
	return 
		os << rom._roma;
}
