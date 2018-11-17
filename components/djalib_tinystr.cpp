// definitions:
#include "mutual\djalib_tinystr.h"

std::ostream& djalib::operator <<(std::ostream& os, const djalib::tinystr& str) {
	str.display(os);
	return os;
}
