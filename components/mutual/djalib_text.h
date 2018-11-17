#pragma once
#ifndef _TEXT_H_
#define _TEXT_H_

#include <iomanip>
#include <sstream>
#include <cassert>
#include <iostream>

namespace djalib
{
	// string:
	unsigned djastrlen(const char* ref_str);
	char* djastrsub(const char* ref_str, int start, int end);
	int djastrcmp(const char *str1, const char *str2);

	//------------------------------
	//------------------------------
	// toString:
	std::string integerToString(int num, int radix = 10);
	std::string doubleToString(double d);

}

#endif
