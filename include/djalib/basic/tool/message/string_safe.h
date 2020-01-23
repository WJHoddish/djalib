#pragma once

// Copyright (C) 2019 Jiaheng Wang. All Rights Reserved.
// This is a gc-attached string.
//

#ifndef DJA_STRING_SAFE_H_
#define DJA_STRING_SAFE_H_

#include "string.h"

#include "gc/gc.h"
#include "reflection/reflection.h"
#include "reflection/reflection_static.h"

namespace dja
{
class StringSafe final : GC_USE, public String
{
  GC_INCLASS(StringSafe)

public:
  StringSafe();

private:
  /// \brief Clean up heap memory.
  void destroy();

  void markChildren();
};
REFLECTION_REGISTER_CLASS(String, StringSafe)
} // namespace dja

#endif