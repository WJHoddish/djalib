#pragma once
// the full version of a self-designed string.
#ifndef _FULLSTR_H_
#define _FULLSTR_H_

#include <cstring>
#include <cassert>
#include <iostream>

#include "djalib_text.h"

namespace djalib
{
	class fullstr
	{
		char*	_data;
		size_t	_size;

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
				// not empty.
				assert(this->_size);
				this->_size = 0;
				delete[] this->_data;
				this->_data = nullptr;
			}
			else {
				// empty.
				assert(!this->_size);
			}
		}

	public:
		fullstr(const char* ref_str = nullptr) {
			init(ref_str);
		}
		fullstr(const fullstr& ref_obj) {
			init(ref_obj.c_str());
		}
		fullstr& operator =(const fullstr& ref_obj) {
			if (this != &ref_obj) {
				destory();
				init(ref_obj.c_str());
			}
			return *this;
		}
		~fullstr() {
			destory();
		}

	public:
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

		int find_first_of(char c) {
			for (size_t idx = 0; idx < this->size(); ++idx) {
				if (this->_data[idx] == c)
					return idx;
			}
			return -1;	// not found.
		}
		int find_last_of(char c) {
			for (size_t idx = (size() - 1); idx >= 0; --idx) {
				if (this->_data[idx] == c)
					return idx;
			}
			return -1;	// not found.
		}

		fullstr substr(size_t pos, unsigned n) const {
			assert(pos < this->size());
			return 
				djastrsub(_data, pos, pos + n);
		}

	public:
		fullstr& operator +=(const fullstr& ref_obj) {
			this->_size += ref_obj.size();
			char* new_data = new char[this->_size + 1];
			strcpy_s(new_data, (this->_size + 1), this->_data);
			strcat_s(new_data, (this->_size + 1), ref_obj.c_str());
			delete[] _data;
			_data = new_data;
			return *this;
		}

		fullstr operator +(const fullstr& ref_obj) const {
			size_t new_size = 
				this->_size + ref_obj.size();
			char* new_data = new char[new_size + 1];
			strcpy_s(new_data, (new_size + 1), this->_data);
			strcat_s(new_data, (new_size + 1), ref_obj.c_str());
			return
				fullstr(new_data);
		}

	public:
		char& operator [](size_t idx) {
			return const_cast<char &>(static_cast<const fullstr&>(*this)[idx]);
		}
		const char& operator [](size_t idx) const {
			assert(idx < this->size());
			return _data[idx];
		}

	public:
		friend std::ostream& operator <<(std::ostream& os, const djalib::fullstr& str);
		void display() {
			std::cout 
				<< "length: " << this->size() 
				<< "\t" << *this << "\n";
		}

	};

}

#endif
