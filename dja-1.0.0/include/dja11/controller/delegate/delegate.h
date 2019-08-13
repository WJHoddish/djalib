#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is the delegate commander.
//
// ________  _______   ___       _______   ________  ________  _________  _______
//|\   ___ \|\  ___ \ |\  \     |\  ___ \ |\   ____\|\   __  \|\___   ___\\  ___ \
//\ \  \_|\ \ \   __/|\ \  \    \ \   __/|\ \  \___|\ \  \|\  \|___ \  \_\ \   __/|
// \ \  \ \\ \ \  \_|/_\ \  \    \ \  \_|/_\ \  \  __\ \   __  \   \ \  \ \ \  \_|/__
//  \ \  \_\\ \ \  \_|\ \ \  \____\ \  \_|\ \ \  \|\  \ \  \ \  \   \ \  \ \ \  \_|\ \
//   \ \_______\ \_______\ \_______\ \_______\ \_______\ \__\ \__\   \ \__\ \ \_______\
//    \|_______|\|_______|\|_______|\|_______|\|_______|\|__|\|__|    \|__|  \|_______|

#ifndef DJA_DELEGATE_H_
#define DJA_DELEGATE_H_

#include <list>
#include <vector>

#include "delstatic.h"
#include "delmember.h"

namespace dja {
	/// \brief The delegate commander.
	///
	/// \attention It uses += & -= to add or remove functions.
	template <typename R, typename... Args>
	class Delegate {
		typedef std::list<IDelegate<R, Args...>*> ListDelegate;
		typedef typename ListDelegate::iterator ListDelegateIterator;
		typedef typename ListDelegate::const_iterator ConstListDelegateIterator;
	public:
		/// \brief The constructor for multi-delegate commander.
		Delegate() {}

		/// \brief The destructor.
		~Delegate() { 
			clear(); 
		}

		/// \brief Add a new delegate.
		Delegate<R, Args...>& operator+=(IDelegate<R, Args...>* _delegate) {
			// traverse the delegate list
			for (ListDelegateIterator iter = delegates_.begin(); iter != delegates_.end(); ++iter) {
				if ((*iter) && (*iter)->compare(_delegate)) {
					// already exist
					delete _delegate;
					return *this;
				}
			}
			// no matter how, update a new delegate (the existing one will be deleted after all)
			delegates_.push_back(_delegate);
			return *this;
		}

		Delegate<R, Args...>& operator-=(IDelegate<R, Args...>* _delegate) {
			for (ListDelegateIterator iter = delegates_.begin(); iter != delegates_.end(); ++iter) {
				if ((*iter) && (*iter)->compare(_delegate)) {
					if ((*iter) != _delegate) {
						// avoid to delete it for twice
						delete (*iter);
					}
					(*iter) = 0;
					break;
				}
			}
			delete _delegate;
			return *this;
		}

		std::vector<R> operator()(Args... params) {
			ListDelegateIterator iter = delegates_.begin();
			std::vector<R> _results;
			while (iter != delegates_.end()) {
				if (0 == (*iter)) {
					iter = delegates_.erase(iter);
				}
				else {
					_results.push_back((*iter)->invoke(params...));
					++iter;
				}
			}
			return _results;
		}

		bool empty() const {
			for (ConstListDelegateIterator iter = delegates_.begin(); iter != delegates_.end(); ++iter) {
				if (*iter) { 
					return false; 
				}
			}
			return true;
		}

		void clear() {
			for (ListDelegateIterator iter = delegates_.begin(); iter != delegates_.end(); ++iter) {
				if (*iter) {
					delete (*iter);
					(*iter) = nullptr;
				}
			}
		}

	private:
		Delegate<R, Args...>(const Delegate& _event);
		Delegate<R, Args...>& operator=(const Delegate& _event);

		ListDelegate delegates_;
	};

	/// \brief Template specialisation for void functions.
	///
	/// For those functions with no return value, there is no need for a vector storing results.
	template <typename... Args>
	class Delegate<void, Args...> {
		typedef std::list<IDelegate<void, Args...>*> ListDelegate;
		typedef typename ListDelegate::iterator ListDelegateIterator;
		typedef typename ListDelegate::const_iterator ConstListDelegateIterator;
	public:
		/// \brief The constructor for multi-delegate commander.
		Delegate() {}

		/// \brief The destructor.
		~Delegate() {
			clear();
		}

		/// \brief Add a new delegate.
		Delegate<void, Args...>& operator+=(IDelegate<void, Args...>* _delegate) {
			// traverse the delegate list
			for (ListDelegateIterator iter = delegates_.begin(); iter != delegates_.end(); ++iter) {
				if ((*iter) && (*iter)->compare(_delegate)) {
					// already exist
					delete _delegate;
					return *this;
				}
			}
			// update a new delegate
			delegates_.push_back(_delegate);
			return *this;
		}

		Delegate<void, Args...>& operator-=(IDelegate<void, Args...>* _delegate) {
			for (ListDelegateIterator iter = delegates_.begin(); iter != delegates_.end(); ++iter) {
				if ((*iter) && (*iter)->compare(_delegate)) {
					if ((*iter) != _delegate) {
						// avoid to delete it for twice
						delete (*iter);
					}
					(*iter) = 0;
					break;
				}
			}
			delete _delegate;
			return *this;
		}

		void operator()(Args... params) {
			ListDelegateIterator iter = delegates_.begin();
			while (iter != delegates_.end()) {
				if (0 == (*iter)) {
					iter = delegates_.erase(iter);
				}
				else {
					(*iter)->invoke(params...);
					++iter;
				}
			}
		}

		bool empty() const {
			for (ConstListDelegateIterator iter = delegates_.begin(); iter != delegates_.end(); ++iter) {
				if (*iter) {
					return false;
				}
			}
			return true;
		}

		void clear() {
			for (ListDelegateIterator iter = delegates_.begin(); iter != delegates_.end(); ++iter) {
				if (*iter) {
					delete (*iter);
					(*iter) = nullptr;
				}
			}
		}

	private:
		Delegate<void, Args...>(const Delegate& _event);
		Delegate<void, Args...>& operator=(const Delegate& _event);

		ListDelegate delegates_;
	};

	/// \brief Three template helper functions.
	template <typename R, typename... Args>
	DelegateStatic<R(*)(Args...)>* make_delegate(R(*func)(Args...)) {
		return new DelegateStatic<R(*)(Args...)>(func);
	}

	template <typename T, typename F>
	DelegateMethod<T, F>* make_delegate(T* _object, F func) {
		return new DelegateMethod<T, F>(_object, func);
	}

	template <typename T>
	DelegateMethod<T, decltype(&T::operator())>* make_delegate(T& func) {
		return new DelegateMethod<T, decltype(&T::operator())>(&func, &T::operator());
	}
}

#endif	// DJA_DELEGATE_H_