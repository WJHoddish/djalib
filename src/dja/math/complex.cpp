// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a class to represent complex numbers.
//

#include "math/complex.h"

#include "gem/judge/sign.h"

#include "gem/operation/pow.h"
#include "gem/operation/sqrt.h"

namespace dja {
// public
Complex::Complex(double r, double i) : r_(r), i_(i) {}

Complex::Complex(const Complex& src) : r_(src.r_), i_(src.i_) {}

Complex& Complex::operator=(const Complex& src) {
  if (this != &src) {
    r_ = src.r_;
    i_ = src.i_;
  }
  return *this;
}

bool Complex::operator==(const Complex& src) const {
  return (r_ == src.r_) && (i_ == src.i_);
}

bool Complex::operator!=(const Complex& src) const {
  return (r_ != src.r_) || (i_ != src.i_);
}

double Complex::modulus() const {
  // TODO(Jiaheng Wang): Using gem functions instead.
  return gem::sqrt(gem::pow(r_, 2) + gem::pow(i_, 2));
}

// friend
const Complex operator+(const Complex& m, const Complex& n) {
  return Complex(m.r_ + n.r_, m.i_ + n.i_);
}

const Complex operator-(const Complex& m, const Complex& n) {
  return Complex(m.r_ - n.r_, m.i_ - n.i_);
}

const Complex operator*(const Complex& m, const Complex& n) {
  return Complex(m.r_ * n.r_ - m.i_ * n.i_, m.i_ * n.r_ + m.r_ * n.i_);
}

const Complex operator/(const Complex& m, const Complex& n) {
  double c = 1.0 / ((n.r_ * n.r_) + (n.i_ * n.i_));
  return Complex(c * ((m.r_ * n.r_) + (m.i_ * n.i_)),
                 c * ((m.i_ * n.r_) - (m.r_ * n.i_)));
}

std::ostream& operator<<(std::ostream& os, const Complex& src) {
  os << src.r_
     << (gem::sign(src.i_) < 0 ?  // is
             '-'
                               :  // or
             '+')                 // positive or zero
     << 'j' << gem::abs(src.i_);
  return os;
}
}  // namespace dja