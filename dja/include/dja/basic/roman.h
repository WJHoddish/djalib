#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a class to represent Roman numbers.
//

#ifndef DJA_ROMAN_H_
#define DJA_ROMAN_H_

#include "dja/tool/tinystr.h"

namespace dja {
	class Roman {
	public:
		/// \brief The constructor.
		Roman(int num = 1);

		/// \brief The copy constructor.
		Roman(const Roman& src);

		/// \brief Comparison.
		bool operator>(const Roman& src);

		bool operator<(const Roman& src);

		friend bool operator==(const Roman& m, const Roman& n);

		/// \brief Arithmetics.
		friend Roman operator+(const Roman& m, const Roman& n);

		friend Roman operator-(const Roman& m, const Roman& n);

		/// \brief The cpp standard output.
		friend std::ostream& operator<<(std::ostream& os, const Roman& src);

	private:
		/// \brief Initialise the object, ensure a correct value for its Arabic numeral.
		bool init(int num);

		/// \brief Set up the string.
		bool romanAssign(int num);

		static const Tinystr B[10], T[10], H[10], K[4];	///< \brief important reference for roman numerals construction
		
		int arb_;		///< \brief the arabic numeral
		Tinystr data_;	///< \brief the roman numeral, a string
	};
}

#endif