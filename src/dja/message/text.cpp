// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a series of functions to manipulate strings and char arrays.
//

#include "message/text.h"

namespace dja {
int strlen(const char* str) {
  if (!str) {
    return -1;
  }
  int i = 0;
  while ((*str++) != '\0') {
    i++;
  }
  return i;
}

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
}  // namespace dja