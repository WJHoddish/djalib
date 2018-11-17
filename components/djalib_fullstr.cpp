// definitions:
#include "mutual\djalib_fullstr.h"

std::ostream& djalib::operator <<(std::ostream& os, const djalib::fullstr& str) {
	os << str._data;
	return os;
}
