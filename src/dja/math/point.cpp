// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// Several sets which are made of different number of points.
//

#include "math/point.h"

namespace dja {
// public
Point2::Point2(double x, double y) : x_(x), y_(y) {}

// friend
std::ostream& operator<<(std::ostream& os, const Point2& src) {
  os << '(' << src.x_ << ", " << src.y_ << ')';
  return os;
}
}  // namespace dja