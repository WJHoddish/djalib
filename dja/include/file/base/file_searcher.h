#pragma once

// Copyright (C) summer 2019 Jiaheng Wang.
// License(BSD)
// Author: Jiaheng Wang
// This is a function set that searches files under a given folder.
//

#ifndef DJA_FILE_SEARCHER_H_
#define DJA_FILE_SEARCHER_H_

#include "file_location.h"

namespace dja {
namespace file {
class FileSearcher : public FileLocation {
 public:
  FileSearcher(std::string path, std::string format = "");

  ~FileSearcher();

  /// \brief Set the flag true to enable recursion searching.
  bool recur();

  /// \brief Scan the target folder to get file names in the vector.
  bool search();

  const std::vector<std::string>& files();

 private:
  bool search(std::string path);

  std::vector<std::string>
      files_;       ///< \brief a vector that stores all file names
  bool recursion_;  ///< \brief whether to get all files even in sub-directories
};
}  // namespace file
}  // namespace dja

#endif  // DJA_FILE_SEARCHER_H_