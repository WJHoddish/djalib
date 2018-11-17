#pragma once
// a smart pointer use reference count.
#ifndef _SMART_PTR_H_
#define _SMART_PTR_H_

#include <cassert>
#include <iostream>

namespace djalib
{
	template<class T>
	class wiseptr
	{
		T* _ptr;			// data.
		int* ref_count;		// reference count (type int pointer, can be easily handled).

		void destroy() {
			assert(!(*ref_count));
			delete _ptr;
			delete ref_count;
			_ptr = nullptr;
			ref_count = nullptr;
		}

	public:
		wiseptr(T* p) :
			_ptr(p) {
			assert(_ptr);

			try {
				ref_count 
					= new int(1);
			}
			catch (...) {
				{
					delete _ptr;
					_ptr = nullptr;
				}
				ref_count = nullptr;
				std::cout 
					<< "(wiseptr) memory allocation failed." << "\n";
				std::system("pause");
				exit(1);
			}
			std::cout 
				<< "(wiseptr) constructor." << "\t\t"
				<< "reference: " << *ref_count << "\n";
		}
		wiseptr(const wiseptr<T>& ref) {
			this->_ptr = ref._ptr;
			this->ref_count = ref.ref_count;
			++(*ref_count);
			std::cout 
				<< "(wiseptr) copy constructor." << "\t"
				<< "reference: " << *ref_count << "\n";
		}
		~wiseptr() {
			std::cout
				<< "(wiseptr) destructor." << "\t\t"
				<< "reference: " << *ref_count << "\n";
			if (--(*ref_count) == 0) {
				destroy();
				std::system("pause");
			}
		}

		wiseptr<T>& operator =(const wiseptr<T>& rhs) {
			// prevent self-assignment!
			++(*rhs.ref_count);

			if (--(*ref_count) == 0) {
				std::cout
					<< "(wiseptr) delete left object." << "\n";
				destroy();
			}

			_ptr = rhs._ptr;
			ref_count = rhs.ref_count;

			std::cout 
				<< "(wiseptr) copy assign." << "\t\t"
				<< "reference: " << *ref_count << "\n";
			return *this;
		}
	};

}

#endif
