#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is an self-defined cpp exception class.
//

#ifndef DJA_ERROR_H_
#define DJA_ERROR_H_

#include <iostream>
#include <stdexcept>
#include <string>

namespace dja
{
class Exception : public std::exception
{
public:
  /// \brief Creates a new exception instance with the given error message.
  Exception(std::string msg);

  /// \brief Frees any memory allocated by the exception.
  virtual ~Exception() noexcept = default;

  /// \brief Prints the exception to the standard error stream (cerr), including
  /// its messageand stack trace if any.
  virtual void dump() const;

  /// \brief Prints the exception to the given output stream, including its
  /// messageand stack trace if any.
  virtual void dump(std::ostream &out) const;

  /// \brief Returns what kind of exception this is.
  ///
  /// \attention In general this returns "error", but in some cases we catch
  /// other kinds of exceptions, and wrap them up as Exceptions. In such case,
  /// the kind will be "int" or "string" etc.
  virtual std::string getKind() const;

  /// \brief Returns the exception's error message as passed to its constructor.
  virtual std::string getMessage() const;

  /// \brief Returns a stack trace for this exception as a multi-line string.
  ///
  /// \attention Not every exception has a proper stack trace,
  /// based on when/why it was thrown, platform incompatibilities, and other
  /// issues. use hasStackTrace to check if a given exception's stack trace is
  /// populated.
  virtual std::string getStackTrace() const;

  virtual bool hasStackTrace() const;

  /// \brief Sets what kind of exception this is, default is "error".
  void setKind(const std::string &str);

  /// \brief Returns the exception's error message as a C string.
  virtual const char *what() const noexcept;

  const static std::string sign_stack_;

protected:
  /// \brief Sets this exception's stack trace to the given multi-line string.
  void setStackTrace(const std::string &str);

private:
  const static std::string sign_;

  std::string msg_, kind_, stack_trace_;
};

/// \brief Prints the error exception to the given output stream.
std::ostream &operator<<(std::ostream &out, const Exception &ex);

/// \brief Signals an error condition in a program by throwing an Exception with
/// the specified message.
[[noreturn]] void error(const std::string &str);
} // namespace dja

#endif // DJA_ERROR_H_
