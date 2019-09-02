#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a derived class for class member functions' registration.
//

#ifndef DJA_DELMEMBER_H_
#define DJA_DELMEMBER_H_

#include "delbase.h"

namespace dja {
	template <typename T, typename R, typename... Args>
	class DelegateMethod : public IDelegate<R, Args...> {};

	/// \brief The specialisation for normal member functions in classes.
	template <typename T, typename R, typename... Args>
	class DelegateMethod<T, R(T::*)(Args...)> : public IDelegate<R, Args...> {
		/// \brief The definition of the function type, where its return and params types are specified.
		typedef R(T::* Method)(Args...);
	public:
		/// \brief The constructor.
		DelegateMethod() {}

		DelegateMethod(T* _object, Method _method)
			:
			object_(_object),
			method_(_method) {}

		virtual ~DelegateMethod() {}

		virtual bool isType(const std::type_info& _type) {
			return (typeid(DelegateMethod<T, R, Args...>) == _type);
		}

		virtual bool compare(IDelegate<R, Args...>* _delegate) const {
			if (0 == _delegate || !_delegate->isType(typeid(DelegateMethod<T, R(T::*)(Args...)>))) {
				return false;
			}
			DelegateMethod<T, R(T::*)(Args...)>* cast = static_cast<DelegateMethod<T, R(T::*)(Args...)>*>(_delegate);
			return (cast->object_ == object_) && (cast->method_ == method_);
		}

		/// \breif The signal of executing the recorded function.
		virtual R invoke(Args...params) {
			return (object_->*method_)(std::forward<Args>(params)...);
		}

	private:
		T* object_;
		Method method_;
	};

	/// \brief Especially for those const member functions in the class.
	template <typename T, typename R, typename... Args>
	class DelegateMethod<T, R(T::*)(Args...)const> : public IDelegate<R, Args...> {
		typedef R(T::* Method)(Args...)const;
	public:
		DelegateMethod() {}

		DelegateMethod(T* _object, const Method _method)
			:
			object_(_object),
			method_(_method) {}

		virtual ~DelegateMethod() {}

		virtual bool isType(const std::type_info& _type) {
			return (typeid(DelegateMethod<T, R(T::*)(Args...)const>) == _type); 
		}

		virtual bool compare(IDelegate<R, Args...>* _delegate) const {
			if (0 == _delegate || !_delegate->isType(typeid(DelegateMethod<T, R(T::*)(Args...)const>))) {
				return false;
			}
			DelegateMethod<T, R(T::*)(Args...)const>* cast = static_cast<DelegateMethod<T, R(T::*)(Args...)const>*>(_delegate);
			return (cast->object_ == object_) && (cast->method_ == method_);
		}

		virtual R invoke(Args...params) {
			return (object_->*method_)(std::forward<Args>(params)...);
		}

	private:
		T* object_;
		Method method_;
	};

}

#endif	// DJA_DELMEMBER_H_
