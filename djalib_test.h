#pragma once

#ifndef _TEST_H_
#define _TEST_H_

#include <iostream>

// you need a Test?
#include "components\mutual\djalib_tinystr.h"
#include "components\mutual\djalib_objectpool.h"
#include "componentsII\design\djalib_reflection.h"

namespace djalib
{
	namespace example
	{
		// universe-use test class.

		class Test_a
		{
			int _data;
			void announce(tinystr str) {
				std::cout
					<< str << "\t"
					<< "value: " << _data << "\t"
					<< "this address: " << this << "\n";
			}

		public:
			Test_a(int num = 0) :
				_data(num) {
				announce("(Test_a) default constructor.");
			}
			~Test_a() {
				announce("(Test_a) destructor.");
			}

		public:
			Test_a(const Test_a& cop) {
				_data = cop._data;
				announce("(Test_a) copy constructor.");
			}
			Test_a(Test_a&& mov) {
				_data = std::move(mov._data);
				announce("(Test_a) move constructor.");
			}

			Test_a& operator =(const Test_a& cop) {
				if (this != &cop) {
					_data = cop._data;
					announce("(Test_a) copy assign.");
				}
				return *this;
			}
			Test_a& operator =(Test_a&& mov) {
				if (this != &mov) {
					_data = std::move(mov._data);
					announce("(Test_a) move assign.");
				}
				return *this;
			}

		public:
			bool operator ==(const Test_a& ref) {
				announce("(Test_a) equal assign.");
				return
					(this->_data == ref._data);
			}

			friend std::ostream& operator <<(std::ostream& os, const Test_a& obj);
			friend int hashCode(Test_a& obj);
		};

		std::ostream& operator <<(std::ostream& os, const Test_a& obj) {
			os << "[" << obj._data << "]";
			return os;
		}

		int hashCode(Test_a& obj) {
			return
				obj._data;
			// looking for a better hash calculating method.
		}

	}

	namespace example
	{
		// Test class relates to Objpool.

		class Test_b
		{
			int		_n;
			int*	_p;
			OBJPOOL_INCLASS(Test_b)

		public:
			// three "must-defined" inclass functions:
			void initial() {
				_n = 0;
				_p = new int(0);
			}
			void release() {
				if (_p) {
					delete _p;
					_p = nullptr;
				}
			}
			void display() {
				std::cout
					<< "value: " << this->_n
					<< "\t" << this->_p;
			}

		public:
			void set(int m, int n) {
				// example: set value to an object.
				_n = m;
				*_p = n;
			}
			int getn() const {
				// example: extract value from an object.
				return _n;
			}

		};
		OBJPOOL_EXCLASS(Test_b)

	}

	namespace example
	{
		// for the reflection class def.

		class Test_c_base
		{
		public:
			Test_c_base() {}
			virtual ~Test_c_base() {}

		public:
			virtual void test() = 0;

		};

		// a necessary inheritance.
		class Test_c : public Test_c_base
		{
		public:
			Test_c() { std::cout << "(Test_c) constructor." << "\n"; }
			~Test_c() { std::cout << "(Test_c) destructor." << "\n"; }

		public:
			virtual void test() { 
				std::cout << "(Test_c)" << "\n"; 
			}
			
		};
		REFLECTION_REGISTER(Test_c_base, Test_c)

	}

	namespace example
	{

	}
}

#endif
