#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a node struct which is going to be applied in advanced data structures.
//

#ifndef DJA_NODE_H_
#define DJA_NODE_H_

namespace dja {
	template <typename T>
	class Node {
	public:
		/// \brief The constructor.
		///
		/// It will call the copy constructor of the type-T variable.
		Node(const T& data)
			:
			data_(data),
			next_(nullptr),
			prev_(nullptr) {}

		/// \brief The destructor.
		~Node() {
			if (next_ != nullptr) {
				next_ = nullptr;
			}
			if (prev_ != nullptr) {
				prev_ = nullptr;
			}
		}

		/// \brief Get members.
		const T& get() const {
			return data_;
		}

		T& get() {
			return data_;
		}

		Node* next_, * prev_;

	private:
		T data_;	///< \brief the template-type object instance
	};
}

#endif	// DJA_NODE_H_