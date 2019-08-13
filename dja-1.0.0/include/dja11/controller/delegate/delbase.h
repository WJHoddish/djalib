#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is an abstract base class to implement delegate in cpp.
//

#ifndef DJA_DELBASE_H_
#define DJA_DELBASE_H_

#include <typeinfo>

namespace dja{
	/// \brief The base APIs for the delegate using RTTI.
	///
	/// \warning It uses variadic templates, where R refers to the return type.
	template <typename R, typename... Args>
	class IDelegate {
	public:
		/// \brier The constructor.
		IDelegate() {}

		/// \brief The virtual destructor.
		virtual ~IDelegate() {}

		virtual bool isType(const std::type_info& _type) = 0;

		virtual bool compare(IDelegate<R, Args...>* _delegate) const = 0;

		/// \brief The invoker.
		virtual R invoke(Args... params) = 0;
	};
}

#endif	// DJA_DELBASE_H_
