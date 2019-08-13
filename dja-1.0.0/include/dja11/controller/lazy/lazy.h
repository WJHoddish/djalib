#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a class implements the lazy evaluation.
//

#ifndef DJA_LAZY_H_
#define DJA_LAZY_H_

#include <memory>
#include <functional>

#include "optional.h"

namespace dja {
	/// \brief This is a class for the lazy evaluation.
	///
	/// A complete expression of function (function body & parameters) is necessary for constructing a lazy instance.
	/// These functions always act as a generator, where the return value will be stored by an Optional member.
	/// In the implementation, the core data (type-T) will not be created instantly,
	/// but the getValue() method is the signal of using and constructing the object you are focusing.
	///
	/// Lazy is designed to deal with the call-by-need situation in cpp.
	template <typename T>
	class Lazy {
	public:
		/// \brief The constructor.
		template <typename Func, typename... Args>
		Lazy(Func& f, Args&& ... args)
			:
			func_([&f, &args...]{ return f(args...); }) {}

		/// \brief At this moment, the lazy instance starts creating your important data.
		///
		/// That's why we call it the lazy evaluation.
		T& getValue() {
			if (!val_.isInit()) {
				val_ = func_();
			}
			return (*val_);
		}

		/// \brief Judge whether the value has been initialised.
		bool isInit() const {
			return val_.isInit();
		}

	private:
		///< \brief an Optional which acts as a box, recording your important data
		Optional<T> val_;

		///< \brief a function (functor) that generates a type-T object
		///
		/// this member is necessary when building a lazy instance, 
		/// it will be firstly set pending, but utilised when the getValue method is called for the first time
		std::function<T()> func_;
	};

	/// \brief The helper function.
	/// 
	/// The helper function for constructing a Lazy object by using lambda expressions.
	///
	/// \warning The helper function can help you create a lazy instance by sending it a lambda expression.
	template <typename Func, typename... Args>
	Lazy<typename std::result_of<Func(Args...)>::type> make_lazy(Func&& fun, Args&& ... args) {
		return Lazy<typename std::result_of<Func(Args...)>::type>(fun, std::forward<Args>(args)...);
	}
}

#endif	// DJA_LAZY_H_