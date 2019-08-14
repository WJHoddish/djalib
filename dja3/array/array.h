#pragma once

// Copyright Jiaheng summer 2019.
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// A multi-dimension array.
//

#ifndef DJA_ARRAY_H_
#define DJA_ARRAY_H_

#include <memory>

#include "array_size.h"
#include "array_ref.h"

namespace dja {
	/// \brief A cpp multi-dimension array implementation.
	template<typename T, int dim_>
	class Marray {
	public:
		/// \brief The constructor.
		Marray(const array_size<dim_>& ref)
			:
			size_(ref),
			data_(new T[ref.total_]) {}

		/// \brief The copy constructor.
		Marray(const Marray<T, dim_>& src)
			:
			size_(src.size_),
			data_(new T[size_.total_]) {
			for (int i = 0; i < size_.total_; ++i) {
				data_[i] = src.data_[i];
			}
		}

		Marray(Marray<T, dim_>&& src)
			:
			size_(src.size_),
			data_(src.data_) {
			src.data_ = nullptr;
		}

		/// \brief The destructor.
		~Marray() {
			if (data_) {
				delete[] data_;
			}
		}

		/// \brief
		array_ref<T, dim_> ref() {
			return array_ref<T, dim_>(size_, data_);
		}

		auto operator[](int index)->decltype(this->ref()[index]) {
			return ref()[index];
		}

		/// \brief Get members.
		int size() const {
			return size_.size_;
		}

		int size_total() const {
			return size_.total_;
		}

	private:
		array_size<dim_> size_;	///< \brief the total size
		T* data_;
	};
}

#endif


