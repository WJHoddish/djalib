// Copyright (C) summer 2019 Jiaheng Wang.
// License(BSD)
// Author: Jiaheng Wang
// This is a function set to help you create all kinds of files.
//

#include "file/base/file_creator.h"

namespace dja {
namespace file {
FileCreator::FileCreator(std::string path, std::string file, std::string format)
    : FileLocation(path, format), file_(file) {}

FileCreator::~FileCreator() {}

std::string FileCreator::file() { return file_ + format_; }

std::string FileCreator::path() { return path_ + t_ + file(); }
}  // namespace file
}  // namespace dja