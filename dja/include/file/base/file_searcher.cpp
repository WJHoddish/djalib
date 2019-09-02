// Copyright (C) summer 2019 Jiaheng Wang.
// License(BSD)
// Author: Jiaheng Wang
// This is a function set that searches files under a given folder.
//

#include "file/base/file_searcher.h"

namespace dja {
namespace file {
FileSearcher::FileSearcher(std::string path, std::string format)
    : FileLocation(path, format), recursion_(false) {}

FileSearcher::~FileSearcher() {}

bool FileSearcher::recur() {
  if (!recursion_) recursion_ = true;
  return recursion_;
}

bool FileSearcher::search() {
  if (files_.empty()) files_.clear();
  return search(path_);
}

bool FileSearcher::search(std::string path) {
#if (defined _WIN32) || (defined _WIN64)
  // in the windows environment
  {
#if (defined _WIN32) && (!defined _WIN64)
    long hFile = 0;
#else
    intptr_t hFile = 0;
#endif
    // a temporary file path
    std::string temp;
    struct _finddata_t fileinfo;
    if ((hFile = _findfirst(temp.assign(path).append(t_).append("*").c_str(),
                            &fileinfo)) != -1) {
      do {
        // current file name
        temp.assign(path).append(t_).append(fileinfo.name);
        // recurse if it is a sub-directory
        if ((fileinfo.attrib & _A_SUBDIR)) {
          if (std::strcmp(fileinfo.name, ".") != 0 &&
              std::strcmp(fileinfo.name, "..") != 0 && recursion_) {
            search(temp);
          }
        } else {
          if (std::strcmp((temp.substr(temp.size() - format_.size())).c_str(),
                          format_.c_str()) == 0) {
            files_.push_back(fileinfo.name);
          }
        }
      } while (_findnext(hFile, &fileinfo) == 0);
      _findclose(hFile);
    }
  }
#endif
#if (defined __x86_64__)
  // in the linux environment
  {}
#endif
  return !files_.empty();
}

const std::vector<std::string>& FileSearcher::files() { return files_; }
}  // namespace file
}  // namespace dja