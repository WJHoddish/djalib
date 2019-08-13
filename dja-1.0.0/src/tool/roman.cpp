// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a class to represent Roman numbers.
//

#include "dja/tool/roman.h"

namespace dja {
	const Tinystr Roman::B[10] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
	const Tinystr Roman::T[10] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
	const Tinystr Roman::H[10] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
	const Tinystr Roman::K[4] = { "", "M", "MM", "MMM" };

	Roman::Roman(int num) {
		init(num);
	}

	Roman::Roman(const Roman& src) {
		init(src.arb_);
	}

	bool Roman::operator>(const Roman& src) {
		return arb_ > src.arb_;
	}

	bool Roman::operator<(const Roman& src) {
		return arb_ < src.arb_;
	}

	bool operator==(const Roman& m, const Roman& n) {
		return m.arb_ == n.arb_;
	}

	Roman operator+(const Roman& m, const Roman& n) {
		return Roman(m.arb_ + n.arb_);
	}

	Roman operator-(const Roman& m, const Roman& n) {
		return Roman(m.arb_ - n.arb_);
	}

	std::ostream& operator<<(std::ostream& os, const Roman& src) {
		return os << src.data_;
	}

	bool Roman::init(int num) {
		bool flag = true;
		if (num <= 0 || num > 3999) {
			// if the input number is out of range, force it to become 1
			num = 1;
			flag = false;
		}
		arb_ = num;
		romanAssign(arb_);
		return flag;
	}

	bool Roman::romanAssign(int num) {
		int div = 1000;
		while (div) {
			int idx = num / div;
			switch (div) {
			case 1000: {
				data_ += K[idx];
				break;
			}
			case 100: {
				data_ += H[idx];
				break;
			}
			case 10: {
				data_ += T[idx];
				break;
			}
			case 1: {
				data_ += B[idx];
			}
			default: {
				//
			}
			}
			// move the numerical digit
			{
				if (div == 1) {
					break;
				}
				else {
					num %= div;
					div /= 10;
				}
			}
		}
		return true;
	}
}