#pragma once

#include "array_size.h"

namespace dja {
	/// \brief The definition to the array_ref
	template <typename T, int dim_>
	class array_ref {
	public:
		/// \brief The constructor.
		array_ref(const array_size<dim_>& size, T* data)
			:
			size_(size),
			data_(data) {}

		/// \brief
		array_ref<T, (dim_ - 1)> operator[](int index) {
			// move the position pointer
			return array_ref<T, (dim_ - 1)>(size_.remains_, data_ + (index * size_.remains_.total_));
		}

		/// \brief Get members.
		int size() const {
			return size_.size_;
		}

		int size_total() const {
			return size_.total_;
		}

	private:
		T* data_;
		const array_size<dim_>& size_;
	};

	/// \brief A specialisation of array_ref
	template <typename T>
	class array_ref<T, 1> {
	public:
		/// \brief The constructor.
		array_ref(const array_size<1> & size, T* data)
			:
			size_(size),
			data_(data) {}

		/// \brief
		///
		/// \return Return a type-T reference that value will be changed exteriorly.
		T& operator[](int index) {
			return data_[index];
		}

		/// \brief Get members.
		int size() const {
			return size_.size_;
		}

		int size_total() const {
			return size_.total_;
		}

	private:
		T* data_;
		const array_size<1> & size_;
	};
}