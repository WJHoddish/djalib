#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a simple observer
// The implementation of delegate is also supported in dja11 in this library.
//

#include <iostream>
#include <string>
#include <functional>
#include <map>

#include "dja/core/noncopyable.h"

namespace dja {
	/// \brief The event list.
	///
	/// \warning Because that all functions are registered by an int number,
	/// please be very careful when removing any function or lambda expression.
	///
	/// \usage
	//// use std::function as function type to define the template event
	//Events<std::function<void(int, int)>> e;
	//auto key = e.connect(print);
	//your_class your_object(...);
	//// register a lambda expression, use [] to capture variables
	//auto key_lambda = e.connect(
	//	[&your_object](int param1, int param2) {
	//		your_object...
	//	});
	//// broadcast
	//e.notify(param1, param2);
	//// remove observer
	//e.disconnect(key);
	template <typename Func>
	class Events : public NonCopyable {
	public:
		/// \brief Add function.
		int connect(const Func& f) {
			return Assgin(f);
		}

		/// \brief Add function with right value.
		int connect(Func&& f) {
			return Assgin(f);
		}

		void disconnect(int key) {
			connections_.erase(key);
		}

		template <typename... Args>
		void notify(Args&& ... args) {
			for (auto& it : connections_) {
				it.second(std::forward<Args>(args)...);
			}
		}

	private:
		template<typename F>
		int assgin(F&& f) {
			int key = observer_id_++;
			connections_.emplace(key, std::forward<F>(f));
			return key;
		}

		int observer_id_ = 0;				///< \brief observer's id
		std::map<int, Func> connections_;	///< \brief observer list
	};
}