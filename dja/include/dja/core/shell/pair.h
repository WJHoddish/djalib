#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a pair structure to combine two data with different types.
//

#ifndef DJA_PAIR_H_
#define DJA_PAIR_H_

namespace dja {
	template <class _T1, class _T2>
	struct Pair {
		/// \brief The constructor (default).
		Pair()
			:
			first(),
			second() {}

		Pair(const _T1& v1, const _T2& v2)
			:
			first(v1),
			second(v2) {}

		/// \brief The copy constructor.
		Pair(const Pair& src)
			:
			first(src.first),
			second(src.second) {}

		/// \brief The template copy constructor.
		///
		/// \warning It performs when needs casting.
		template <class _U1, class _U2>
		Pair(const Pair<_U1, _U2>& ref)
			:
			first(ref.first),
			second(ref.second) {}

		/// \brief
		Pair& operator=(const Pair& src) {
			first = src.first;
			second = src.second;
			return (*this);
		}

		_T1 first;	///< \brief the first data
		_T2 second;	///< \brief and the second one
	};

	/// \brief Define all relational operators.
	template<class _T1, class _T2>
	inline bool operator==(const Pair<_T1, _T2>& lhs, const Pair<_T1, _T2>& rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template<class _T1, class _T2>
	inline bool operator!=(const Pair<_T1, _T2>& lhs, const Pair<_T1, _T2>& rhs) {
		return (!(lhs == rhs));
	}

	template<class _T1, class _T2>
	inline bool operator<(const Pair<_T1, _T2>& lhs, const Pair<_T1, _T2>& rhs) {
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template<class _T1, class _T2>
	inline bool operator>(const Pair<_T1, _T2>& lhs, const Pair<_T1, _T2>& rhs) {
		return (rhs < lhs);
	}

	template<class _T1, class _T2>
	inline bool operator<=(const Pair<_T1, _T2>& lhs, const Pair<_T1, _T2>& rhs) {
		return (!(rhs < lhs));
	}

	template<class _T1, class _T2>
	inline bool operator>=(const Pair<_T1, _T2>& lhs, const Pair<_T1, _T2>& rhs) {
		return (!(lhs < rhs));
	}
}

#endif	// DJA_PAIR_H_