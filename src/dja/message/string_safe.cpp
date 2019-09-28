// Copyright (C) 2019 Jiaheng Wang. All Rights Reserved.
// This is a gc-attached string.
//

#include "message/string_safe.h"

namespace dja
{
// public
StringSafe::StringSafe() : String() {}

// private
void markChildren() {}

void StringSafe::destroy()
{
  // release heap content
}
} // namespace dja
