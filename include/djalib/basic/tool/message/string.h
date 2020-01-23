#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a string based on the heap-allocated char array in cpp.
//

#ifndef DJA_STRING_H_
#define DJA_STRING_H_

#include <iostream>

#include "message/text.h"

namespace dja
{
class String
{
public:
  /// \brief The constructor (public).
  ///
  /// \warning The pointer input could be a nullptr, judgement is required.
  String(const char *data);

  /// \brief The destructor.
  ///
  /// \attention Declare as a virtual function then derived classes will benefit
  /// from.
  virtual ~String();

  /// \brief Assign it a new value by a String object.
  String &operator=(const String &src);

  /// \attention Fixed the bug of adding itself.
  String &operator+=(const String &src);

  const char &operator[](size_t idx) const;

  char &operator[](size_t idx);

  // \brief Refresh the string.
  void rebuild(const String &src);

  /// \brief Return a char array in the style of C.
  const char *c_str() const;

  /// \brief Solve the length of the string.
  const int size() const;

protected:
  String();

private:
  /// \brief Init string with a default "nullptr".
  ///
  /// \param data  Which the default is "nullptr".
  /// \attention Ensure that
  void init(const char *ref = nullptr);

  void destroy();

  ///< \brief the pointer to the heap-allocated char array
  char *data_;

  ///< \brief length of the string
  int size_;

  /// \brief Using cpp standard output.
  friend std::ostream &operator<<(std::ostream &os, const String &src);
};
} // namespace dja
#endif
