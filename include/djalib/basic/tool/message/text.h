#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a series of functions to manipulate strings and char arrays.
//

#ifndef DJA_TEXT_H_
#define DJA_TEXT_H_

namespace dja
{
/// \brief Solve the length of the string.
int strlen(const char *str);

/// \brief Compare and determine whether two strings are identical.
///
/// \return Return 0 if they are completely the same, otherwise return an
/// integer.
int strcmp(const char *str_1, const char *str_2);
} // namespace dja

#endif