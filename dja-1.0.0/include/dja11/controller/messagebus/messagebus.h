#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a complete cpp implementation of the message bus, it also uses the cpp RTTI.
//

#include <map>
#include <string>

#include "dja11/controller/messagebus/traits.h"
#include "dja/core/noncopyable.h"
#include "dja/core/shell/any.h"

#ifndef DJA_MESSAGEBUS_H_
#define DJA_MESSAGEBUS_H_

namespace dja {
	/// \brief The message bus commander.
	///
	/// This class maintains a map that records topic(std::string)-function type pair as elements.
	///
	/// \attention In use, you can register several lambda expressions under one topic with a certain function type.
	class MessageBus : public NonCopyable {
	public:
		/// \brief Message registration.
		template <typename F>
		void attach(F&& f, const std::string& topic = "") {
			auto func = to_function(std::forward<F>(f));
			add(topic, std::move(func));
		}

		/// \brief Send message.
		template <typename R>
		void send(const std::string& topic = "") {
			using function_type = std::function<R()>;
			std::string msg_type = topic + typeid(function_type).name();
			auto range = map_.equal_range(msg_type);
			for (std::multimap<std::string, Any>::iterator it = range.first; it != range.second; ++it) {
				auto f = it->second.any_cast <function_type>();
				f();
			}
		}

		template <typename R, typename... Args>
		void send(Args&& ... args, const std::string& topic = "") {
			using function_type = std::function<R(Args...)>;
			std::string msg_type = topic + typeid(function_type).name();
			auto range = map_.equal_range(msg_type);
			for (std::multimap<std::string, Any>::iterator it = range.first; it != range.second; ++it) {
				auto f = it->second.any_cast <function_type>();
				f(std::forward<Args>(args)...);
			}
		}

		/// \brief Remove a topic.
		///
		/// \attention It needs the topic name and the function type.
		template <typename R, typename... Args>
		void remove(const std::string& topic = "") {
			using function_type = std::function<R(Args...)>;
			std::string msg_type = topic + typeid(function_type).name();
			auto range = map_.equal_range(msg_type);
			// erase the topic-function type pair from the private map
			map_.erase(range.first, range.second);
		}

	private:
		template <typename F>
		void add(const std::string& topic, F&& f) {
			std::string msg_type = topic + typeid(F).name();
			map_.emplace(std::move(msg_type), std::forward<F>(f));
		}

		std::multimap<std::string, Any> map_;
	};
}

#endif	// DJA_MESSAGEBUS_H_
