#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// A doubly linked list implementation.
//

#ifndef DJA_LINKEDLIST_H_
#define DJA_LINKEDLIST_H_

#include "dja/structure/node.h"

namespace dja {
	template <typename T>
	class DoublyList {
	public:
		/// \brief The constructor.
		DoublyList()
			:
			size_(0),
			head_(nullptr),
			tail_(nullptr) {}

		/// \brief The destructor.
		~DoublyList() {
			clear();
		}

		/// \brief 
		///
		/// \return Returns a reference to the element in the linked list container,
		/// If searching out of range, return a default type-T object.
		/// Therefore, it requires type-T objects to have a default constructor.
		const T& operator[](int idx) const {
			int cursor = 0;
			Node<T>* temp = head_;
			while (temp != nullptr) {
				if (cursor == idx) { return temp->get(); }
				temp = temp->next_;
				cursor++;
			}
			return T();
		}

		/// \brief If the structure is empty.
		bool empty() const {
			return !size_;
		}

		/// \brief Tell you the actual size.
		int size() const {
			return size_;
		}

		/// \brief Insert a new element into the list.
		///
		/// This function adds the first data if the list is empty, or attach the data after the tail.
		///
		/// \return If allocation failed return false, otherwise return true after inserting the new data.
		bool insert(const T& n_data) {
			// copy the input data on the heap
			Node<T>* n_node;
			if (!allocNode(n_node, n_data)) { return false; }
			else {
				if (empty()) { tail_ = head_ = n_node; }
				else {
					n_node->prev_ = tail_;
					tail_->next_ = n_node;
					tail_ = n_node;
				}
				size_++;
			}
			return true;
		}

		/// \brief Traverse the structure and clear the whole structure by deleting heap memory.
		///
		/// \attention If the temp is null at the beginning, there is definitely no head or tail, and nothing in the list.
		bool clear() {
			Node<T>* prev, * temp;
			{
				prev = nullptr;
				temp = head_;
			}
			while (temp != nullptr) {
				prev = temp;
				temp = temp->next_;
				{ delete prev; prev = nullptr; }
				size_--;
			}
			head_ = tail_ = nullptr;
			return true;
		}

	private:
		/// \brief To make sure all nodes are allocated on the heap.
		///
		/// \return The object has been successfully constructed?
		bool allocNode(Node<T>*& n_node, const T& n_data) {
			try {
				n_node = new Node<T>(n_data);
			}
			catch (...) {
				n_node = nullptr;
				return false;
			}
			return true;
		}

		///< \brief the actual list size
		size_t size_;

		///< \brief the head and tail node in the list
		Node<T>* head_, * tail_;
	};
}

#endif	// DJA_LINKEDLIST_H_