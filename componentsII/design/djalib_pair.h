#pragma once

#ifndef _PAIR_H_
#define _PAIR_H_

#include <iostream>

namespace djalib
{
	template <class _T1, class _T2>
	struct Pair
	{
		_T1 _first;
		_T2 _second;

		Pair() :
			_first(), _second() {	// this will call the "default constructor"!
				{
					std::cout
						<< "(Pair) default constructor." << "\n";
				}
		}
		Pair(const _T1 &a, const _T2 &b) :
			_first(a), _second(b) {
				{
					std::cout
						<< "(Pair) para constructor." << "\n";
				}
		}
		template <class _U1, class _U2>
		Pair(const Pair<_U1, _U2>& ref) :
			_first(ref._first), _second(ref._second) {
				{
					std::cout 
						<< "(Pair) copy constructor." << "\n";
				}
		}
	};
	
	template <class _T1, class _T2>
	Pair<_T1, _T2> make_pair(_T1 x, _T2 y) {
		return (Pair<_T1, _T2>(x, y));
	}

}

#endif
