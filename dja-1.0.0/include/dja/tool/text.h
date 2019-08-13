#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a series of functions to manipulate strings and char arrays.
//

#ifndef DJA_TEXT_H_
#define DJA_TEXT_H_

#include <cstddef>

namespace dja {
	/// \brief Compare and determine whether two strings are identical.
	/// \return Return 0 if they are completely the same, otherwise return an integer.
	int strcmp(const char* str_1, const char* str_2);

	/// \brief Extract a substring from a string by defining indexes of both terminals.
	char* strsub(const char* str, int start, int end);

	/// \brief Solve the length of the string.
	unsigned strlen(const char* str);

}

#endif	// DJA_TEXT_H_