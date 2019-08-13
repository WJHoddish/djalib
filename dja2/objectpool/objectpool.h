#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a modern cpp object pool.
//

#ifndef DJA_OBJECTPOOL_H_
#define DJA_OBJECTPOOL_H_

#include <queue>
#include <vector>
#include <memory>
#include <functional>

#include "../error/error.h"

namespace dja {
	/// \brief A modern cpp object pool.
	template <typename T>
	class ObjectPool {
	public:
		/// \brief The constructor.
		ObjectPool(int chunk_size = default_chunk_size_) {
			if (chunk_size <= 0) {
				error("object pool chunk size must be positive");
			}
			chunk_size_ = chunk_size;
			allocateChunk();
		}

		ObjectPool(const ObjectPool<T>& src) = delete;

		ObjectPool<T>& operator=(const ObjectPool<T>& rhs) = delete;

		/// \brief Reserves an object for use.
		std::shared_ptr<T> acquireObject() {
			if (free_list_.empty()) {
				allocateChunk();
			}
			// move next free object from the queue to a local smart pointer
			std::unique_ptr<T> obj(std::move(free_list_.front()));
			free_list_.pop();
			std::shared_ptr<T> obj_shared(obj.release(), [this](T* t)
				{
					free_list_.push(std::unique_ptr<T>(t));
				});
			return obj_shared;
		}

	private:
		/// \brief Allocates mChunkSize new objects and adds them to mFreeList.
		void allocateChunk() {
			for (int i = 0; i < chunk_size_; ++i) {
				free_list_.emplace(std::make_unique<T>());
			}
		}

		static const int default_chunk_size_;

		int chunk_size_;

		///< \brief the list stores the objects that are not currently in use by clients]
		std::queue<std::unique_ptr<T>> free_list_;
	};

	template <typename T>
	const int ObjectPool<T>::default_chunk_size_ = 10;
}

#endif	// DJA_OBJECTPOOL_H_
