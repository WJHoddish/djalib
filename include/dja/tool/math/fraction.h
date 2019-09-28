#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a class that represents fraction numbers.
//

#ifndef DJA_FRACTION_H_
#define DJA_FRACTION_H_

#include <iostream>

namespace dja {
class Fraction {
 public:
  /// \brief The constructor.
  ///
  /// If only one number is given, the fraction will be n/1 equals to n.
  Fraction(int n = 0, int d = 1);

  /// \brief The copy constructor.
  Fraction(const Fraction& src);

  /// \brief Value assignment.
  ///
  /// \return Its reference to do make a chain in the expression.
  Fraction& operator=(const Fraction& src);

  /// \brief The minus sign for fractions.
  const Fraction operator-();

  /// \brief Calculate the value in decimal form.
  double value() const;

  /// \brief Calculate the reciprocal.
  Fraction reciprocal() const;

  /// \brief Comparison.
  friend bool operator==(const Fraction& m, const Fraction& n);

  friend bool operator!=(const Fraction& m, const Fraction& n);

  /// \brief 4 basic arithmetics.
  friend const Fraction operator+(const Fraction& m, const Fraction& n);

  friend const Fraction operator-(const Fraction& m, const Fraction& n);

  friend const Fraction operator*(const Fraction& m, const Fraction& n);

  friend const Fraction operator/(const Fraction& m, const Fraction& n);

  /// \brief The cpp standard output.
  friend std::ostream& operator<<(std::ostream& os, const Fraction& src);

 private:
  /// \brief An automatic action when the object is constructed.
  ///
  /// To simplify the representation of fractions.
  void simplify();

  ///< \brief The numerator and denominator of the fraction
  int n_, d_;
};
}  // namespace dja

#endif  // DJA_FRACTION_H_