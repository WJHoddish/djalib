#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is .
//

#ifndef DJA_TRAIT_H_
#define DJA_TRAIT_H_

#include <functional>

namespace dja {
	/// \brief Transform into the std::function or function pointer.
	template <typename T>
	struct TraitsFunction;

	/// \brief For normal functions.
	template <typename R, typename... Args>
	struct TraitsFunction<R(Args...)> {
	public:
		enum { arity = sizeof...(Args) };
		typedef R function_type(Args...);
		typedef R return_type;
		typedef R(*pointer)(Args...);
		using stl_function_type = std::function<function_type>;

		template <size_t I>
		struct args {
			static_assert(I < arity, "index is out of range, index must less than sizeof Args");
			using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
		};

		typedef std::tuple<std::remove_cv_t<std::remove_reference_t<Args>>...> tuple_type;
		typedef std::tuple<std::remove_const_t<std::remove_reference_t<Args>>...> bare_tuple_type;
	};

	/// \brief For the function pointer.
	template <typename R, typename... Args>
	struct TraitsFunction<R(*)(Args...)> : TraitsFunction<R(Args...)> {};

	/// \brief For std::function.
	template <typename R, typename... Args>
	struct TraitsFunction<std::function<R(Args...)>> : TraitsFunction<R(Args...)> {};

	/// \brief For functors.
	template<typename Callable>
	struct TraitsFunction : TraitsFunction<decltype(&Callable::operator())> {};

	template <typename F>
	typename TraitsFunction<F>::stl_function_type to_function(const F& lambda) {
		return static_cast<typename TraitsFunction<F>::stl_function_type>(lambda);
	}

	template <typename F>
	typename TraitsFunction<F>::stl_function_type to_function(F&& lambda) {
		return static_cast<typename TraitsFunction<F>::stl_function_type>(std::forward<F>(lambda));
	}

	template <typename F>
	typename TraitsFunction<F>::pointer to_function_pointer(const F& lambda) {
		return static_cast<typename TraitsFunction<F>::pointer>(lambda);
	}

#define FUNCTION_TRAITS(...)																	\
	template <typename R, typename ClassType, typename... Args>									\
	struct TraitsFunction<R (ClassType::*)(Args...) __VA_ARGS__> : TraitsFunction<R(Args...)>	\
	{																							\
	};

	FUNCTION_TRAITS()
		FUNCTION_TRAITS(const)
		FUNCTION_TRAITS(volatile)
		FUNCTION_TRAITS(const volatile)
}

#endif	// DJA_TRAITS_H_
