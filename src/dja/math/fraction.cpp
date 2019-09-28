// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a class that represents fraction numbers.
//

#include "math/fraction.h"

#include "gem/operation/lcm.h"

namespace dja {
// public
Fraction::Fraction(int n, int d) : n_(n), d_(d) { simplify(); }

Fraction::Fraction(const Fraction& src) : n_(src.n_), d_(src.d_) {}

Fraction& Fraction::operator=(const Fraction& src) {
  if (this != &src) {
    n_ = src.n_;
    d_ = src.d_;
  }
  return *this;
}

const Fraction Fraction::operator-() { return Fraction(n_ * (-1), d_); }

double Fraction::value() const {
  return static_cast<double>(n_) / static_cast<double>(d_);
}

Fraction Fraction::reciprocal() const { return (int)1 / (*this); }

// private
void Fraction::simplify() {
  // ensure the denominator is positive
  if (d_ < 0) {
    n_ *= -1;
    d_ *= -1;
  }
  // TODO(Jiaheng Wang): Using gem functions instead.
  auto c = gem::gcd(n_, d_);
  // apply the reduction of a fraction
  n_ /= c;
  d_ /= c;
}

// friend
bool operator==(const Fraction& m, const Fraction& n) {
  return (m.value() == n.value());
}

bool operator!=(const Fraction& m, const Fraction& n) { return !(m == n); }

const Fraction operator+(const Fraction& m, const Fraction& n) {
  // TODO(Jiaheng Wang): Using gem functions instead.
  auto c = gem::lcm(m.d_, n.d_);
  return Fraction(c / m.d_ * m.n_ + c / n.d_ * n.n_, c);
}

const Fraction operator-(const Fraction& m, const Fraction& n) {
  // TODO(Jiaheng Wang): Using gem functions instead.
  int c = gem::lcm(m.d_, n.d_);
  return Fraction(c / m.d_ * m.n_ - c / n.d_ * n.n_, c);
}

const Fraction operator*(const Fraction& m, const Fraction& n) {
  return Fraction(m.n_ * n.n_, m.d_ * n.d_);
}

const Fraction operator/(const Fraction& m, const Fraction& n) {
  return Fraction(m.n_ * n.d_, m.d_ * n.n_);
}

std::ostream& operator<<(std::ostream& os, const Fraction& src) {
  os << src.n_ << "/" << src.d_;
  return os;
}
}  // namespace dja