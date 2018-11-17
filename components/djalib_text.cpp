// definitions:
#include "mutual\djalib_text.h"

int djalib::djastrcmp(const char *str1, const char *str2) {
	// if the same, return '0'.
	while (*str1 == *str2) {
		if (*str1 == '\0')
			return 0;
		str1++;
		str2++;
	}
	// else return an integer...
	return *str1 - *str2;
}

unsigned djalib::djastrlen(const char* ref_str) {
	unsigned i = 0;
	while ((*ref_str++) != '\0') {
		i++;
	}
	return i;
}

char* djalib::djastrsub(const char* ref_str, int start, int end) {
	char* new_str = new char[end - start + 1];
	char* str = new_str;
	for (int i = start; i < end; ++i) {
		if (ref_str[i] == '\0')
			break;
		*new_str = ref_str[i];
		new_str++;
	}
	*new_str = '\0';
	return str;
}

//------------------------------
//------------------------------
std::string djalib::integerToString(int num, int radix) {
	assert(
		radix == 8 ||
		radix == 10 ||
		radix == 16);

	std::ostringstream stream;
	if (radix != 10) {
		stream << std::setbase(radix);
	}
	stream << num;
	return stream.str();
}

std::string djalib::doubleToString(double d) {
	std::ostringstream stream;
	stream << std::uppercase << d;
	return stream.str();
}
