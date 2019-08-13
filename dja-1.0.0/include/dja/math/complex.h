#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a class to represent complex numbers.
//

#ifndef DJA_COMPLEX_H_
#define DJA_COMPLEX_H_

#include "dja/math/math.h"

namespace dja {
	class Complex {
	public:
		/// \brief The constructor.
		///
		/// If only one number is given, the imaginary part has a default value which is 0.
		Complex(double r = 0.0, double i = 0.0);

		/// \brief The copy constructor.
		Complex(const Complex& src);

		/// \brief
		/// \return Return its reference to do assignment operations continuously in the expression.
		Complex& operator=(const Complex& src);

		/// \brief The distance to the complex plane origin.
		double modulus() const;

		/// \brief Comparison.
		bool operator==(const Complex& src) const;

		bool operator!=(const Complex& src) const;

		/// \brief 4 basic arithmetics.
		friend const Complex operator+(const Complex& m, const Complex& n);

		friend const Complex operator-(const Complex& m, const Complex& n);

		friend const Complex operator*(const Complex& m, const Complex& n);

		friend const Complex operator/(const Complex& m, const Complex& n);

		/// \brief The cpp standard output.
		friend std::ostream& operator<<(std::ostream& os, const Complex& src);

	protected:
		/// \brief Display the class in the console.
		void display(std::ostream& os) const;

	private:
		///< the real and imaginary part of the complex
		double r_, i_;
	};
}

#endif