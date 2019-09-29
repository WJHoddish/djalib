#pragma once

// Copyright (C) 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
//

#ifndef DJA_FOR_EACH_H_
#define DJA_FOR_EACH_H_

#include <type_traits>

namespace dja {
template <class T>
auto move(T&& t) -> typename std::remove_reference<T>::type&& {
  using R = typename std::remove_reference<T>::type&&;
  return static_cast<R>(t);
}

/// \brief My for_each.
///
/// \attention The input function (most likely to be a functor) is input as a
/// reference. Assume it owns a mechanism to keep a log when processing each
/// element.
/// Return nothing, which is the main difference from the std::for_each.
template <typename Iterator, typename F>
void for_each(Iterator beg, Iterator end, F& f) {
  while (beg != end) {
    // call the function/functor
    f(*beg);
    // move the pointer/iterator
    ++beg;
  }
  return /*return type is transformed by std::move in C++11*/;
}
}  // namespace dja

#endif