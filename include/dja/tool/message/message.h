#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// Further sub-classes MessageSafe/Message... will be derived from this
//

#ifndef DJA_MESSAGE_H_
#define DJA_MESSAGE_H_

namespace dja
{
class Message
{
protected:
  /// \brief The max size of the string.
  enum
  {
    STRING_SIZE = 64
  };
};
} // namespace dja

#endif