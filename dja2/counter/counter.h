#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is an infinite number counter.
//

#ifndef DJA_COUNTER_H_
#define DJA_COUNTER_H_

#include <vector>
#include <iostream>

#include "../objectpool/cobjectpool.h"

namespace dja {
	class Counter {
	public:
		/// \brief The constructor.
		Counter(int num = 0);

		Counter(const Counter& src);

		~Counter();

		Counter& operator =(const Counter& rhs);

		friend std::ostream& operator <<(std::ostream& os, Counter& src);

	private:
		/// \brief The number value represented by vector will be increased.
		void increase(std::vector<int>& vec, int num);

		void decrease(std::vector<int>& vec, int num);

		/// \brief .
		void destroy();

		static const int counter_system;

		std::vector<int>* vec_;

		///< \brief the reference count
		int* cnt_;
	};
}

#endif