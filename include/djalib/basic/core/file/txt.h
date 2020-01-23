#pragma once

// Copyright (C) summer 2019 Jiaheng Wang.
// License(BSD)
// Author: Jiaheng Wang
// Create .txt files.
//

#ifndef DJA_FILE_TXT_H_
#define DJA_FILE_TXT_H_

#include "file/base/file_creator.h"

namespace dja {
namespace file {
/// \brief Create a .txt file.
class txt : public FileCreator {
 public:
  txt(std::string path, std::string file) : FileCreator(path, file, ".txt") {}
};
}  // namespace file
}  // namespace dja

#endif