#pragma once
#ifndef _ROMAN_H_
#define _ROMAN_H_

// a class represents roman numerals (range: 1 ~ 3999).

#include <string>
#include <iostream>
#include "djalib_text.h"
#include "djalib_tinystr.h"

namespace djalib
{
	class Roman
	{
		int		_arb;		// data.
		tinystr	_roma;		// data.
		static const tinystr 
			B[10], T[10], H[10], K[4];	// important reference for roman numerals construction.

		void init(int num) {
			assert(num > 0 && num <= 3999);
			_arb = num;
			romanAssign(_arb);
		}

	public:
		Roman() {
			init(1);
		}
		Roman(int num) {
			init(num);
		}
		Roman(const Roman& ref) {
			init(ref._arb);
		}

		// there is no "overload: =", since all instance vars are in the stack.
		// in a similar way, any explicit destructor is unnecessary.

	protected:
		void romanAssign(int num) {
			assert(num > 0 && num <= 3999);
			int div = 1000;
			while (div) {
				int idx = num / div;
				switch (div) {
				case 1000:
					_roma += K[idx]; break;
				case 100:
					_roma += H[idx]; break;
				case 10:
					_roma += T[idx]; break;
				case 1:
					_roma += B[idx]; break;
				default: break;
				}
				if (div == 1) { break; }
				else {
					num %= div;
					div /= 10;
				}
			}
		}

	public:
		friend std::ostream& operator <<(std::ostream& os, const Roman& rom);

		friend Roman operator +(const Roman& m, const Roman& n);
		friend Roman operator -(const Roman& m, const Roman& n);

		friend bool operator ==(const Roman& m, const Roman& n);
		bool operator >(const Roman& ref);
		bool operator <(const Roman& ref);

	};

}

#endif
