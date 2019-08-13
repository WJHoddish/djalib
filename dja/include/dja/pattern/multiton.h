#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a base class for the singleton, multiton dessign pattern.
//

#ifndef DJA_MULTITON_H_
#define DJA_MULTITON_H_

#include <utility>
#include <stdexcept>
#include <string>
#include <memory>
#include <map>

namespace dja {
	/// \brief The single & multiton.
	///
	/// \usage
	//// set up an instance
	//dja::Multiton < ${ type_name } > ::instance(${ instance_name }, args);
	//// use the instance
	//std::shared_ptr < ${ type_name } > obj = dja::Multiton < ${ type_name } > ::getInstance(${ instance_name });
	//// destroy all instances
	//dja::Multiton < ${ type_name } > ::destroyInstance();
	template <typename T>
	class Singleton {
	public:
		/// \brief Create an instance on the heap.
		///
		/// \warning You have to initialise the instance for the singleton before using it.
		template <typename... Args>
		static T* instance(Args&& ... args) {
			if (instance_ == nullptr) {
				instance_ = new T(std::forward<Args>(args)...);
			}
			return instance_;
		}

		/// \brief Return the same instance.
		static T* getInstance() {
			if (instance_ == nullptr) {
				throw std::logic_error("the instance is not init, please initialise the instance first");
			}
			return instance_;
		}

		/// \brief Destroy the instance by releasing its heap memory.
		static void destroyInstance() {
			if (instance_) {
				delete instance_;
				instance_ = nullptr;
			}
		}

	private:
		Singleton();
		virtual ~Singleton();
		Singleton(const Singleton&);
		Singleton& operator=(const Singleton&);
		Singleton& operator=(Singleton&&);

		///< define the instance initial value
		static T* instance_;
	};

	template <typename T>
	T* Singleton<T>::instance_ = nullptr;

	/// \brief A base class for the multiton class/object.
	///
	/// It uses the same idea of building singleton.
	template <typename T, typename K = std::string>
	class Multiton {
	public:
		/// \brief Add a new instance into the map.
		template <typename... Args>
		static std::shared_ptr<T> instance(const K& key, Args&& ... args) {
			std::shared_ptr<T> instance = nullptr;
			auto it = map_.find(key);
			if (it == map_.end()) {
				instance = std::make_shared<T>(std::forward<Args>(args)...);
				map_.emplace(key, instance);
			}
			return instance;
		}

		/// \brief Fetch a certain instance based on its key value.
		template <typename Key>
		static std::shared_ptr<T> getInstance(const Key& key) {
			std::shared_ptr<T> instance = nullptr;
			auto it = map_.find(key);
			if (it != map_.end()) {
				instance = it->second;
			}
			return instance;
		}

		/// \brief Destroy all multitons by clearing the global map up.
		static void destroyInstance() {
			if (!map_.empty()) {
				map_.clear();
			}
		}

	private:
		Multiton();
		virtual ~Multiton();
		Multiton(const Multiton&);
		Multiton& operator=(const Multiton&);
		Multiton& operator=(Multiton&&);

		static std::map<K, std::shared_ptr<T>> map_;
	};

	template <typename T, typename K>
	std::map<K, std::shared_ptr<T>> Multiton<T, K>::map_;
}

#endif	// DJA_MULTITON_H_