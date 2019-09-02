// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is an self-defined cpp exception class.
//

#include "core/error.h"

namespace dja {
const std::string Exception::sign_ = "Djalib Error: ";

const std::string Exception::sign_stack_ = "Stack trace: ";

Exception::Exception(std::string msg) : msg_(sign_ + msg), kind_("error") {}

void Exception::dump() const { dump(std::cerr); }

void Exception::dump(std::ostream& out) const {
  if (!msg_.empty()) {
    out << msg_;
  }
  if (hasStackTrace()) {
    out << "\n" << getStackTrace();
  }
  out.flush();
}

std::string Exception::getKind() const { return kind_; }

std::string Exception::getMessage() const { return msg_; }

bool Exception::hasStackTrace() const { return !stack_trace_.empty(); }

std::string Exception::getStackTrace() const { return stack_trace_; }

void Exception::setKind(const std::string& str) { kind_ = str; }

void Exception::setStackTrace(const std::string& str) { stack_trace_ = str; }

/// \brief The std style error announcement.
const char* Exception::what() const noexcept { return msg_.c_str(); }

std::ostream& operator<<(std::ostream& out, const Exception& e) {
  out << e.what();
  std::string stack = e.getStackTrace();
  if (!stack.empty()) {
    out << Exception::sign_stack_ << std::endl << stack;
    out.flush();
  }
  return out;
}

void error(const std::string& str) { throw Exception(str); }
}  // namespace dja