#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a C++ implementation inverse of control (IoC) container.
//

#ifndef DJALIB_IOC_H_
#define DJALIB_IOC_H_

#include <string>
#include <functional>
#include <unordered_map>
#include <iostream>

#include "noncopyable.h"
#include "counted_ptr.h"
#include "any.h"

namespace dja {
	/// \brief The inverse-of-control container.
	///
	/// The inverse-of-control container is a design pattern
	/// that helps you create objects after registering constructors of your classes.
	class Ioc : public NonCopyable {
	public:
		Ioc() {}

		~Ioc() {}

		/// \brief Using this interface to register your constructors.
		///
		/// To register the type as a string-key in the std::map (unordered).
		/// Use a closure to erase parameter's data type.
		///
		/// \attention The usage of ioc requires an "interface" type and a specific type.
		/// You need to define a base class as an "interface", then the container can help you create
		/// an object of the interface type (what gives you is a std smart pointer).
		/// Otherwise, your interface type should have a constructor that only receives a specific type pointer.
		template <class T, class Depend, typename ...Args>
		typename std::enable_if<!std::is_base_of<T, Depend>::value>::type
			typeRegister(const std::string& key)
		{
			// No inheritance relationship.
			std::function<T* (Args...)> func =
				[](Args...args) {
				return new T(new Depend(args...));
			};
			typeRegister(key, func);
		}

		template <class T, class Depend, typename ...Args>
		typename std::enable_if<std::is_base_of<T, Depend>::value>::type
			typeRegister(const std::string& key)
		{
			// T is the base class of Depend.
			std::function<T* (Args...)> func =
				[](Args...args) {
				return new Depend(args...);
			};
			typeRegister(key, func);
		}

		/// \brief The main interface that helps create a method instance.
		template <class T, typename ...Args>
		std::shared_ptr<T> resolveShared(const std::string& key, Args... args) {
			T* t = resolve<T>(key, args...);
			return std::shared_ptr<T>(t);
		}

		/// \brief To resolve the creator.
		template <class T, typename... Args>
		T* resolve(const std::string& key, Args... args) {
			if (creator_map_.find(key) == creator_map_.end()) {
				return nullptr;
			}
			Any resolver = creator_map_[key];
			std::function<T* (Args...)> function = resolver.any_cast<std::function<T * (Args...)>>();
			return function(args...);
		}

	private:
		/// \brief Erase the data type by using closure.
		void typeRegister(const std::string& key, Any constructor) {
			if (creator_map_.find(key) != creator_map_.end()) {
				throw std::invalid_argument("an existing key!");
			}
			else {
				creator_map_.emplace(key, constructor);
			}
		}

		std::unordered_map<std::string, Any> creator_map_;
	};

	/// \brief The base caller.
	///
	/// \attention Please use this base class to define you interface class.
	/// Your interface will keep the pointer wisely by reference count.
	template <typename T>
	class IocCaller {
	public:
		IocCaller(T* ptr) :
			ptr_(ptr) {}

		~IocCaller() {}

	protected:
		counted_ptr<T> ptr_;
	};
}

#endif