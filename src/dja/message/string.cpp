// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a string based on the heap-allocated char array in cpp.
//

#include "string.h"

namespace dja
{
// public
String::String(const char *data) : data_(nullptr), size_(0) { init(data); }

String::~String() { destroy(); }

String &String::operator=(const String &src)
{
  if (this != &src)
  {
    rebuild(src);
  }
  return *this;
}

String &String::operator+=(const String &src)
{
  char *data;
  // set up the new length after expansion
  int size_1 = size_;
  int size_2 = src.size();
  int size = size_1 + size_2;
  // maintain a heap-allocated char array
  data = new char[static_cast<size_t>(size) + 1];
  data[size] = '\0';
  // paste chars
  for (int i = 0; i < size; ++i)
  {
    if (i < size_1)
    {
      data[i] = data_[i];
    }
    else
    {
      data[i] = src.c_str()[i - size_1];
    }
  }
  // delete the original data
  destroy();
  {
    data_ = data;
    size_ = size;
  }
  return *this;
}

const char &String::operator[](size_t idx) const
{
  // obtain the character at the right position
  return data_[idx];
}

char &String::operator[](size_t idx)
{
  return const_cast<char &>(static_cast<const String &>(*this)[idx]);
}

void String::rebuild(const String &src)
{
  destroy();
  init(src.c_str());
}

const char *String::c_str() const { return data_; }

const int String::size() const { return size_; }

// protected
String::String() : data_(nullptr), size_(0) { init(); }

// private
void String::init(const char *ref)
{
  if (ref)
  {
    size_ = strlen(ref);
  }
  else
  {
    // init by the nullptr as default
    size_ = 0;
  }
  // maintain a heap-allocated char array
  data_ = new char[static_cast<size_t>(size_) + 1];
  data_[size_] = '\0';
  // paste chars
  if (ref)
  {
    for (int i = 0; i < size_; ++i)
    {
      data_[i] = ref[i];
    }
  }
}

void String::destroy()
{
  if (data_ != nullptr)
  {
    {
      delete[] data_;
      data_ = nullptr;
    }
    size_ = 0;
  }
}

// friend
std::ostream &operator<<(std::ostream &os, const String &src)
{
  os << src.data_;
  return os;
}
} // namespace dja