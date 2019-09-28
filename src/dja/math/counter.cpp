// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is an infinite number counter.
//

#include "counter.h"

namespace dja {
	Counter::Counter(int num)
		:
		vec_(new std::vector<int>),
		cnt_(new int(1)) {
		vec_->push_back(0);
		increase(*vec_, num);
	}

	Counter::Counter(const Counter& src) {
		{ vec_ = src.vec_; cnt_ = src.cnt_; }
		++(*cnt_);
	}

	Counter::~Counter() {
		if (--(*cnt_) == 0) { destroy(); }
	}

	Counter& Counter::operator =(const Counter& rhs) {
		++(*rhs.cnt_);
		if (--(*cnt_) == 0) { destroy(); }
		{ vec_ = rhs.vec_; cnt_ = rhs.cnt_; }
		return *this;
	}

	std::ostream& operator <<(std::ostream& os, Counter& src) {
		int size = static_cast<int>(src.vec_->size()) - 1;
		for (int i = size; i > 0; --i) {
			os << (*(src.vec_))[i] << "<<";
		}
		{
			os << (*(src.vec_))[0];
		}
		return os;
	}

	void Counter::increase(std::vector<int>& vec, int num) {
		int per = (num % counter_system + vec[vec.size() - 1]) % counter_system;
		int div = (num % counter_system + vec[vec.size() - 1]) / counter_system + num / counter_system;
		vec[vec.size() - 1] = per;
		if (div > 0) {
			vec.push_back(0);
			increase(vec, div);
		}
		else { return; }
	}

	void Counter::destroy() {
		if (vec_) {
			delete vec_;
			vec_ = nullptr;
		}
		if (cnt_) {
			delete cnt_;
			cnt_ = nullptr;
		}
	}

	const int Counter::counter_system = 1024;
}
