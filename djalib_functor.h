#pragma once

#ifndef _FUNCTOR_h_
#define _FUNCTOR_h_

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

#include "components\counter\djalib_counter.h"

namespace djalib
{
	// imitation of "std::for_each()".
	template <class Iterator, class Functor>
	typename Functor& For_Each(Iterator begin, Iterator end, Functor& fn) {
		while (begin != end) {
			fn(*begin);
			++begin;
		}
		return fn;
	}
	
	//------------------------------
	//------------------------------
	class Counter
	{
		counter _counter;

	public:
		void operator()(int element) const {
			_counter += (element);
		}

	public:
		const counter getCounter() { return _counter; }

	};

	//------------------------------
	//------------------------------
	class Averager
	{
		size_t _count;
		double _average;

	public:
		void operator ()(int num) {
			// a new num is added, when the fuctor is called.
			_count++;
			_average += (num - _average) / (_count);

			std::cout << "value: " << num << ", average: " << _average << "\n";
		}

	public:
		Averager() :
			_count(0), _average(0) {
			// pass.
		}

	public:
		const double getAverage() { return this->_average; }

	};

	//------------------------------
	//------------------------------
	class Modulo
	{
	public:
		double operator()(double a, double b) {
			assert(a || b);
			return sqrt((a * a) + (b * b));
		}
	};

	//------------------------------
	//------------------------------

}

#endif
