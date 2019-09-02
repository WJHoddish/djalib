#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a cpp implementation meta class using RTTI for type erase.
//

#ifndef DJA_ANY_MAP_H_
#define DJA_ANY_MAP_H_

#include "any.h"

#include <string>
#include <unordered_map>

#include "shell/counted_ptr.h"
#include "shell/exclusive_ptr.h"
#include "controller/noncopyable.h"

namespace dja {
typedef std::unordered_map<std::string, Any> AnyMap;
}

#endif