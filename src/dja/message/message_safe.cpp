// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a message box.
//

#include "message_safe.h"

namespace dja {
COBJECTPOOL_EXCLASS(MessageSafe)

// private
void MessageSafe::init(const char src[]) {
  std::memset(data_, '\0', STRING_SIZE);
  // copy the char array bit by bit
  for (int i = 0; i < STRING_SIZE || src[i] == '\0'; ++i) {
    data_[i] = src[i];
  }
}

void MessageSafe::destroy() {
  // clear up the array
  std::memset(data_, '\0', STRING_SIZE);
}

// friend
std::ostream& operator<<(std::ostream& os, MessageSafe& src) {
  os << src.data_;
  return os;
}

void MessageDisplay::operator()(MessageSafe& ref) const {
  // display the message within a line.
  std::cout << ref << std::endl;
}
}  // namespace dja