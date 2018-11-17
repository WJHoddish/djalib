// definitions:
#include "mutual\djalib_point.h"

std::ostream& djalib::operator <<(std::ostream& os, const djalib::Point& pt) {
	return 
		os << pt.toString();
}
