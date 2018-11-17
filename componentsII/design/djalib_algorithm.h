#pragma once
// compare using "hashCode()".
#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <cassert>
#include <iostream>

namespace djalib
{
	class Algorithm
	{
	public:
		// comparison:
		template <typename T>
		static bool is_smaller(const T& m, const T& n) {
			return
				m.hashCode() < n.hashCode();
		}
		template <typename T>
		static bool is_larger(const T& m, const T& n) {
			return
				m.hashCode() > n.hashCode();
		}
		template <typename T>
		static bool is_equal(const T& m, const T& n) {
			return
				m.hashCode() == n.hashCode();
		}	// "const T&" is necessary. 

		//------------------------------
		//------------------------------
	public:
		// sort:

		


		//------------------------------
		//------------------------------
	protected:
		// accessories£º
		template <typename T>
		static void Swap(T& m, T& n) {
			// a copy of stl::swap().
			T temp(m);
			m = n;
			n = temp;
		}
	};

}

#endif
