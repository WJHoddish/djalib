// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a string implementation in cpp.
//

#include "dja/tool/tinystr.h"

namespace dja {
	Tinystr::Tinystr(const char* data) {
		init(data);
	}

	Tinystr::Tinystr(const Tinystr& src) {
		init(src.c_str());
	}

	Tinystr::~Tinystr() {
		destroy();
	}

	Tinystr& Tinystr::operator=(const Tinystr& src) {
		if (this != &src) {
			destroy();
			init(src.c_str());
		}
		return *this;
	}

	const char* Tinystr::c_str() const {
		return data_;
	}

	bool Tinystr::clear() {
		if (destroy()) {
			// destroy, then rebuild the string
			return init();
		}
		else {
			return false;
		}
	}

	const size_t Tinystr::size() const {
		return size_;
	}

	Tinystr& Tinystr::operator+=(const Tinystr& src) {
		// solve the new length
		size_ += src.size();
		// set up a new string with the length after expansion
		char* new_data = new char[size_ + 1];
		{
			std::strcpy(new_data, data_);
			std::strcat(new_data, src.c_str());
		}
		// delete the original one
		{
			delete[] data_;
			data_ = new_data;
		}
		return *this;
	}

	const char& Tinystr::operator[](size_t idx) const {
		return data_[idx];
	}

	char& Tinystr::operator[](size_t idx) {
		return const_cast<char&>(static_cast<const Tinystr&>(*this)[idx]);
	}

	std::ostream& operator<<(std::ostream& os, const Tinystr& src) {
		src.display(os);
		return os;
	}

	void Tinystr::display(std::ostream& os) const {
		if (*(data_) == '\0') {
			// this is an empty string
			os << "nil";
		}
		else {
			// print out all characters in sequence
			for (size_t idx = 0; idx < size(); ++idx) {
				os << data_[idx];
			}
		}
	}

	bool Tinystr::init(const char* ref) {
		if (ref == nullptr) {
			// the input is null
			size_ = 0;
			data_ = new char[size_ + 1];
			*(data_) = '\0';
		}
		else {
			size_ = strlen(ref);
			data_ = new char[size_ + 1];
			std::strcpy(data_, ref);
		}
		return true;
	}

	bool Tinystr::destroy() {
		if (*(data_) != '\0') {
			size_ = 0;
			{
				delete[] data_;
				data_ = nullptr;
			}
			return true;
		}
		else {
			// the string has nothing
			return false;
		}
	}
}