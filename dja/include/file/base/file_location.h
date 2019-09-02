#pragma once

// Copyright (C) summer 2019 Jiaheng Wang.
// License(BSD)
// Author: Jiaheng Wang
// A class set with inheritance relationships, offering functions to manipulate
// files.
//

#ifndef DJA_FILE_LOCATION_H_
#define DJA_FILE_LOCATION_H_

#if (defined _WIN32) || (defined _WIN64)
#include <direct.h>
#include <io.h>
#endif

#if (defined __x86_64__)
#include <dirent.h>
#include <sys/io.h>
#endif

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace dja {
namespace file {
///< \brief the separator is different in win/unix
#if (defined _WIN32) || (defined _WIN64)
const std::string t_ = "\\";
#else
const std::string t_ = "/";
#endif

class File {
 public:
  /// \brief The _mkdir.
  ///
  /// \return true: already exists or has been successfullt created, false:
  /// failed to init the folder.
  static bool mkdir(std::string path);

  /// \brief The _rmdir.
  ///
  /// \attention Just like the func above, if you achieve the goal, return true,
  /// otherwise return false.
  static bool rmdir(std::string path);
};

/// \brief Offer the folder where the file locates, the file format.
class FileLocation {
 public:
  FileLocation(std::string path, std::string format);

  virtual ~FileLocation();

 protected:
  ///< \brief the path where you wanna to deal with (read/write)
  std::string path_;
  ///< \brief which kind of file you prefer (e.g. ".jpg")
  std::string format_;
};
}  // namespace file
}  // namespace dja

#endif  // DJA_FILE_LOCATION_H_