#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a derived class for normal functions' registration.
//

#ifndef DJA_DELSTATIC_H_
#define DJA_DELSTATIC_H_

#include "delbase.h"

namespace dja {
	template <typename R, typename... Args>
	class DelegateStatic : public IDelegate<R, Args...> {};

	template <typename R, typename... Args>
	class DelegateStatic<R(*)(Args...)> : public IDelegate<R, Args...> {
		/// \brief The definition of the function type, where its return and params types are specified.
		typedef  R(*Func)(Args...);
	public:
		/// \brief The constructor.
		DelegateStatic(Func _func)
			:
			func_(_func) {}

		/// \brief The destructor.
		virtual ~DelegateStatic() {}

		virtual bool isType(const std::type_info& _type) {
			return (typeid(DelegateStatic<R, Args...>) == _type);
		}

		virtual bool compare(IDelegate<R, Args...>* _delegate) const {
			if (_delegate == 0 || !_delegate->isType(typeid(DelegateStatic<R(*)(Args...)>))) {
				return false;
			}
			DelegateStatic<R(*)(Args...)>* cast = static_cast<DelegateStatic<R(*)(Args...)>*>(_delegate);
			return (cast->func_ == func_);
		}

		/// \breif The signal of executing the recorded function.
		virtual R invoke(Args... params) {
			return func_(std::forward<Args>(params)...);
		}

	private:
		Func func_;
	};

}

#endif	// DJA_DELSTATIC_H_