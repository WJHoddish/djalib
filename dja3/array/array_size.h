#pragma once

#ifndef DJA_ARRAY_SIZE_H_
#define DJA_ARRAY_SIZE_H_

namespace dja {
	/// \brief The definition to the array_size.
	template <int dim_>
	struct array_size {
		/// \brief The constructor.
		array_size(int size, const array_size<(dim_ - 1)>& remains)
			:
			size_(size),
			total_(size* remains.total_),
			remains_(remains) {}

		/// \brief
		///
		/// \attention The expression: (remains_, nsize_) calls the overload,.
		array_size<(dim_ + 1)> operator,(int n_size) {
			return array_size<(dim_ + 1)>(size_, (remains_, n_size));
		}

		array_size<(dim_ - 1)> remains_;	///< \brief the subarray of the main
		int	size_, total_;					///< \brief the array size
	};

	/// \brief A specialisation of array_size
	template <>
	struct array_size<0> {
		array_size()
			:
			total_(1) {}

		array_size<(1)> operator,(int nsize_) {
			return array_size<(1)>(nsize_, array_size<0>());
		}

		int total_;
	};

	typedef array_size<0> array_sizes;
}

#endif
