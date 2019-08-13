#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a string implementation in cpp.
//

#ifndef DJA_TINYSTR_H_
#define DJA_TINYSTR_H_

#include <iostream>
#include <cstring>

#include "dja/tool/text.h"

namespace dja {
	class Tinystr {
	public:
		/// \brief The constructor.
		Tinystr(const char* data = nullptr);

		/// \brief The copy constructor.
		Tinystr(const Tinystr& src);

		/// \brief The destructor.
		~Tinystr();

		/// \brief =.
		///
		/// \return Return the reference for the chain expression.
		Tinystr& operator=(const Tinystr& src);

		/// \brief The std style type cast.
		const char* c_str() const;

		/// \brief Refresh the string.
		bool clear();

		/// \brief Solve the length of the string.
		const size_t size() const;

		/// \brief Append another string at the end.
		Tinystr& operator+=(const Tinystr& src);

		/// \brief Extract the element at the exact position of the string.
		///
		/// \warning Remember not to input an index out of boundary.
		const char& operator[](size_t idx) const;

		char& operator[](size_t idx);

		/// \brief The cpp standard output.
		friend std::ostream& operator<<(std::ostream& os, const Tinystr& src);

	protected:
		/// \brief Display the class in the console.
		void display(std::ostream& os) const;

	private:
		/// \brief Initialise the char string.
		bool init(const char* ref = nullptr);

		/// \brief Clean up the memory allocated for the string.
		bool destroy();

		char* data_;	///< \brief the pointer to the char array
		size_t size_;	///< \brief length of the string
	};
}

#endif
