#pragma once

// Copyright (C) summer 2019 Jiaheng Wang.
// License(BSD)
// Author: Jiaheng Wang
// This is a function set to help you create all kinds of files.
//

#ifndef DJA_FILE_CREATOR_H_
#define DJA_FILE_CREATOR_H_

#include "file_location.h"

namespace dja {
namespace file {
class FileCreator : public FileLocation {
 public:
  /// \brief The constructor.
  ///
  /// \param path The forder name.
  /// \param file The file name.
  ///
  /// \attention The third parameter is not set default, a specific file format
  /// should be given.
  FileCreator(std::string path, std::string file, std::string format);

  virtual ~FileCreator();

  /// \brief Get the name of file with its format info.
  std::string file();

  /// \brief Get the full path to locate the file in your system.
  std::string path();

 protected:
  ///< \brief the name of file you wanna create
  std::string file_;
  ///< \brief the file writer
  std::ofstream fout_;
};
}  // namespace file
}  // namespace dja

#endif  // DJA_FILE_CREATOR_H_