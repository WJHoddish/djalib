#pragma once

#ifndef _TINY_STRING_h_
#define _TINY_STRING_h_

#include <cstring>
#include <cassert>
#include <iostream>

namespace djalib
{
	class tinystr
	{
		char*	_data;		// pointer to the char string.
		size_t	_size;		// the length.

		void init(const char* ref_str = nullptr) {
			if (!ref_str) {
				this->_size = 0;
				this->_data = new char[this->_size + 1];
				*(this->_data) = '\0';
			}
			else {
				this->_size = strlen(ref_str);
				this->_data = new char[this->_size + 1];
				strcpy_s(this->_data, (this->_size + 1), ref_str);
			}
		}
		void destory(void) {
			if (*(this->_data) != '\0') {
				assert(this->_size);
				this->_size = 0;
				delete[] this->_data;
				this->_data = nullptr;
			}
			else
				assert(!this->_size);
		}

	public:
		// constructor:
		tinystr(const char* ref_str = nullptr) {
			init(ref_str);
		}
		// copy constructor (deep copy):
		tinystr(const tinystr& ref_obj) {
			init(ref_obj.c_str());
		}
		// overload: "=" (deep copy):
		tinystr& operator =(const tinystr& ref_obj) {
			if (this != &ref_obj) {
				destory();
				init(ref_obj.c_str());
			}
			// chain addressing:
			return *this;
		}

		// destructor:
		~tinystr() {
			destory();
		}

	public:
		// other functions:
		const char* c_str() const {
			return this->_data;
		}
		const size_t size() const {
			assert(_size == strlen(_data));
			return this->_size;
		}
		void clear(void) {
			destory();
			init();
		}

	public:
		tinystr& operator +=(const tinystr& ref_obj) {
			this->_size += ref_obj.size();
			char* new_data = new char[this->_size + 1];
			strcpy_s(new_data, (this->_size + 1), this->_data);
			strcat_s(new_data, (this->_size + 1), ref_obj.c_str());
			delete[] _data;
			_data = new_data;
			return *this;
		}

		char& operator [](size_t idx) {
			return const_cast<char &>(static_cast<const tinystr&>(*this)[idx]);
		}
		const char& operator [](size_t idx) const {
			// avoid out of boundary:
			assert(idx < this->size());
			return _data[idx];
		}

	public:
		friend std::ostream& operator <<(std::ostream& os, const djalib::tinystr& str);

	protected:
		void display(std::ostream& os) const {
			if (*(this->_data) == '\0') {
				std::cout
					<< "NULL";
			}
			else {
				for (size_t idx = 0; idx < this->size(); ++idx) {
					std::cout
						<< this->_data[idx];
				}
			}
		}

	};

}

#endif
