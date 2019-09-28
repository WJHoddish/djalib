// Copyright (C) summer 2019 Jiaheng Wang.
// License(BSD)
// Author: Jiaheng Wang
// A class set with inheritance relationships, offering functions to manipulate
// files.
//

#include "file/base/file_location.h"

namespace dja {
namespace file {
bool File::mkdir(std::string path) {
  if (0 != ::_access(path.c_str(), 0)) {
    // if this folder not exist, create a new one
    return !::_mkdir(path.c_str());
  }
  return true;
}

bool File::rmdir(std::string path) {
  if (0 == ::_access(path.c_str(), 0)) {
    // if the folder is here, delete it.
    return ::_rmdir(path.c_str());
  }
  return true;
}

FileLocation::FileLocation(std::string path, std::string format)
    : path_(path), format_(format) {}

FileLocation::~FileLocation() {}
}  // namespace file
}  // namespace dja