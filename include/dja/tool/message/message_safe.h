#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a message box, and objects are always allocated in an object pool.
//

#ifndef DJA_MESSAGE_SAFE_H_
#define DJA_MESSAGE_SAFE_H_

#include <iostream>

#include "message.h"

#include "op/cobjectpool.h"

namespace dja
{
class MessageSafe final : public Message
{
  COBJECTPOOL_INCLASS(MessageSafe)

  /// \brief Initiate the message string.
  ///
  /// \attention Usage: MessageSafe* p_str = MessageSafe::create("hello,
  /// world");
  void init(const char src[]);

  /// \brief Erase the message string.
  ///
  /// \attention Usage: p_str->clear();
  void destroy();

  ///< \brief a char array with const length
  char data_[STRING_SIZE];

  friend std::ostream &operator<<(std::ostream &os, MessageSafe &src);
};

/// \brief Display each message line by line.
///
/// \attention The class might be given to the pool for "mapAll".
class MessageDisplay
{
public:
  void operator()(MessageSafe &ref) const;
};
} // namespace dja

#endif