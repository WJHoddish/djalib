#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// Several sets which are made of different number of points.
//

#ifndef DJA_POINTS_H_
#define DJA_POINTS_H_

#include <iostream>

namespace dja {
class Point2 {
 public:
  Point2(double x = 0.0, double y = 0.0);

  /// \brief The cpp standard output.
  friend std::ostream& operator<<(std::ostream& os, const Point2& src);

 private:
  ///< \brief coordinates
  double x_, y_;
};

class Point3 {};

typedef Point2 Arrow2;

typedef Point3 Arrow3;
}  // namespace dja

#endif