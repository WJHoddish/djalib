#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// A thread-safe hash table implementation.
//

#ifndef DJA_HASHTABLE_H_
#define DJA_HASHTABLE_H_

#include <functional>
#include <shared_mutex>

namespace dja {
	/// \brief The node in the hash bucket.
	template <typename K, typename V>
	class HashNode {
	public:
		/// \brief The constructor.
		///
		/// \warning It requires type-K & type-V objects to have a copy constructor.
		HashNode(const K& key, const V& data)
			:
			key_(key),
			data_(data),
			next_(nullptr) {}

		/// \brief The destructor.
		~HashNode() {
			if (next_ != nullptr) {
				next_ = nullptr;
			}
		}

		/// \brief Get members.
		const K& getKey() const {
			return key_;
		}

		const V& getValue() const {
			return data_;
		}

		/// \brief Set members.
		/// \warning It requires type-T objects to overload the assignment operator.
		void setValue(const V& n_data) {
			data_ = n_data;
		}

		HashNode* next_;

	private:
		K key_;		///< \brief the hash key
		V data_;	///< \brief the template data
	};

	/// \brief The bucket in the hash table.
	template <typename K, typename V>
	class HashBucket {
	public:
		/// \brief The constructor.
		HashBucket()
			:
			head_(nullptr) {}

		/// \brief The destructor.
		~HashBucket() {
			clear();
		}

		/// \brief Insert new elements.
		///
		/// The key value for each node is unique in the structure.
		/// Corresponding value will be updated once the key is found to exist.
		///
		/// \return Return a false if the bucket merely updates an existing element,
		/// otherwise return a true if a new element is truely appended.
		///
		/// \warning it requires type-K objects to have the overload!=.
		bool insert(const K& key, const V& n_data) {
			// an exclusive lock to enable single write in the bucket
			std::unique_lock<std::shared_timed_mutex> lock(mutex_);
			HashNode<K, V>* prev, * temp;
			{
				prev = nullptr;
				temp = head_;
			}
			while (temp != nullptr && temp->getKey() != key) {
				// search the target till the last node
				prev = temp;
				temp = temp->next_;
			}
			if (temp != nullptr) {
				// the key is found in bucket, update its value
				temp->setValue(n_data);
				return false;
			}
			else {
				// the key is not found, then set up a new one
				if (head_ == nullptr) {
					// the bucket is empty, add the first element
					head_ = new HashNode<K, V>(key, n_data);
				}
				else {
					// attach the new element at the end of the list
					prev->next_ = new HashNode<K, V>(key, n_data);
				}
				return true;
			}
		}

		/// \brief Remove an existing element with a certain key.
		///
		/// \return Return a false if the key is not found, or return a true if anything is truely deleted.
		bool remove(const K& key) {
			// an exclusive lock to enable single write in the bucket
			std::unique_lock<std::shared_timed_mutex> lock(mutex_);
			HashNode<K, V>* prev, * temp;
			{
				prev = nullptr;
				temp = head_;
			}
			while (temp != nullptr && temp->getKey() != key) {
				prev = temp;
				temp = temp->next_;
			}
			if (temp == nullptr) {
				// the key is not found, and nothing will happen
				return false;
			}
			else {
				// fix the structure of the list with the node location
				if (temp == head_) {
					head_ = temp->next_;
				}
				else {
					prev->next_ = temp->next_;
				}
				// erase the node from the bucket
				{
					delete temp;
					temp = nullptr;
				}
				return true;
			}
		}

		/// \brief Search the target element according to its key, and extract the value of it.
		///
		/// \return Return a false if the key is not found, otherwise assign the value.
		bool search(const K& key, V& ex_data) const {
			// a shared mutex is used to enable mutiple concurrent reads
			std::shared_lock<std::shared_timed_mutex> lock(mutex_);
			HashNode<K, V>* temp = head_;
			while (temp != nullptr) {
				if (temp->getKey() == key) {
					// the key is found, the object passed in will be assigned a new value
					ex_data = temp->getValue();
					return true;
				}
				temp = temp->next_;
			}
			// value not found
			ex_data = V();
			return false;
		}

		/// \brief Clear the list up.
		void clear() {
			// an exclusive lock to enable single write in the bucket
			std::unique_lock<std::shared_timed_mutex> lock(mutex_);
			HashNode<K, V>* prev, * temp;
			{
				prev = nullptr;
				temp = head_;
			}
			while (temp != nullptr) {
				// traverse the list
				prev = temp;
				temp = temp->next_;
				{
					delete prev;
					prev = nullptr;
				}
			}
			head_ = nullptr;
		}

	private:
		HashNode<K, V>* head_;					///< the head node of the bucket
		mutable std::shared_timed_mutex mutex_;	///< the mutex for this bucket
	};

	/// \brief The thread-safe hash table.
	template <typename K, typename V, typename F = std::hash<K>>
	class HashMap {
	public:
		/// \brief The constructor.
		///
		/// It creates an array allocated on the heap, which consists of several HashBucket (singly linked-lists).
		/// \attention The const member must be defined when constructing.
		HashMap(size_t size = 1031)
			:
			table_(new HashBucket<K, V>[size]),
			size_(size) {}

		/// \brief The destructor.
		~HashMap() {
			delete[] table_;
			table_ = nullptr;
		}

		/// \attention Actions of copy or move are prohibited.
		HashMap(const HashMap&) = delete;
		HashMap(HashMap&&) = delete;
		HashMap& operator=(const HashMap&) = delete;
		HashMap& operator=(HashMap&&) = delete;

		/// \brief Insert a new node. 
		///
		/// If the key already exists, update the value, else insert a new node in the bucket with the key-value pair.
		void insert(const K& key, const V& n_data) {
			size_t key_ = fn_(key) % size_;
			table_[key_].insert(key, n_data);
		}

		/// \brief Remove an existing node, since the key is exclusive in the table.
		void remove(const K& key) {
			size_t key_ = fn_(key) % size_;
			table_[key_].remove(key);
		}

		/// \brief Search the target element according to its key, and extract the value of it.
		///
		/// \return Return a false if the key is not found, otherwise assign the value.
		bool search(const K& key, V& ex_data) const {
			size_t key_ = fn_(key) % size_;
			return table_[key_].search(key, ex_data);
		}

		/// \brief Clear the table up by deleting lists one by one.
		void clear() {
			for (size_t i = 0; i < size_; ++i) {
				table_[i].clear();
			}
		}

	private:
		const size_t size_;			///< \brief the hash size

		F fn_;						///< \brief the hash function
		HashBucket<K, V>* table_;	///< \brief the table body
	};
}

#endif	// DJA_HASHTABLE_H_