// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a series of functions to manipulate strings and char arrays.
//

#include "dja/tool/text.h"

namespace dja {
	int strcmp(const char* str_1, const char* str_2) {
		while (*str_1 == *str_2) {
			if (*str_1 == '\0' && *str_2 == '\0') {
				return 0;
			}
			str_1++;
			str_2++;
		}
		return (*str_1 - *str_2);
	}

	char* strsub(const char* str, int start, int end) {
		size_t len = static_cast<size_t>(end) - static_cast<size_t>(start) + 1;
		char* sub = new char[len];
		// record the head address of the substring
		char* res = sub;
		for (int i = start; i < end; ++i) {
			// traverse the fragment
			if (str[i] == '\0') {
				break;
			}
			else {
				// move the pointer position
				*sub = str[i];
				sub++;
			}
		}
		*sub = '\0';
		return res;
	}

	unsigned strlen(const char* str) {
		size_t len = 0;
		while ((*str++) != '\0') {
			len++;
		}
		return len;
	}
}