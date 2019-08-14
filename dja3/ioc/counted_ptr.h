#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a shared pointer using reference count.
//

#ifndef DJA_COUNTEDPTR_H_
#define DJA_COUNTEDPTR_H_

namespace dja {
	/// \brief This is a smart pointer using reference count.
	template <typename T>
	class counted_ptr {
	public:
		/// \brief The constructor, no default constructor for this class..
		///
		/// \warning Please ensure that the input pointer is pointing to a heap.
		counted_ptr(T* ptr)
			:
			ptr_(ptr),
			cnt_(new int(1)) {}

		/// \brief The copy constructor.
		///
		/// \attention It only does copy for pointers.
		counted_ptr(const counted_ptr<T>& src) {
			{ ptr_ = src.ptr_; cnt_ = src.cnt_; }
			++(*cnt_);
		}

		/// \brief The destructor.
		///
		/// Release the memory if and only if this is the last reference
		~counted_ptr() {
			if (--(*cnt_) == 0) {
				destroy();
			}
		}

		/// \brief Operator overload for value assignment.
		///
		/// \return Return the object itself for the chain expression.
		///
		/// \attention It only does copy for pointers.
		counted_ptr<T>& operator =(const counted_ptr<T>& rhs) {
			// to prevent self-assignment
			++(*rhs.cnt_);
			if (--(*cnt_) == 0) {
				destroy();
			}
			{ ptr_ = rhs.ptr_; cnt_ = rhs.cnt_; }
			return *this;
		}

		/// \brief Operator overload for *, ->.
		counted_ptr<T>& operator *() {
			return *this;
		}

		counted_ptr<T>* operator ->() {
			return this;
		}

		/// \brief Get members, the current reference count.
		int count() const {
			return *cnt_;
		}

		/// \brief Return the raw pointer of the data.
		///
		/// \return Return a const pointer that cannot call its non-const functions.
		const T* raw_ptr() const {
			return ptr_;
		}

		T* raw_ptr() {
			// this is a non-protetcted pointer
			return ptr_;
		}

	private:
		/// \brief Eliminate this instance, release the memory if this is the last reference.
		void destroy() {
			if (ptr_ != nullptr) { delete ptr_; ptr_ = nullptr; }
			if (cnt_ != nullptr) { delete cnt_; cnt_ = nullptr; }
		}

		T* ptr_;	///< \brief the data pointer
		int* cnt_;	///< \brief the counter for the reference count mechanism, be easily handled during copying
	};
}

#endif	// DJA_COUNTEDPTR_H_