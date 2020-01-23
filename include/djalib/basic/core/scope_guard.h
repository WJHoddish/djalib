#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a cpp scopeguard, which ensures a Garbage Collection function will be called when exception occurs.
//

#ifndef DJA_SCOPEGUARD_H_
#define DJA_SCOPEGUARD_H_

#include <type_traits>

namespace dja {
	/// \brief The scope guard to protect your memory from unexpected termination.
	///
	/// \usage
	//try {
	//	std::function<void()> f = [] {
	//		std::cout << "cleanup from unnormal exit" << "\n";
	//	};
	//	{
	//		auto gd = make_guard(f);
	//		//...
	//		throw std::string("Djalib Error: some exception);
	//	}
	//}
	//catch (...) {
	//	// f will be automatically called in this block
	//}
	template <typename F>
	class ScopeGuard {
	public:
		/// \brief The constructor.
		explicit ScopeGuard(const F& f) 
			: 
			func_(f), 
			dismiss_(false) {}

		explicit ScopeGuard(F&& f) 
			: 
			func_(std::move(f)), 
			dismiss_(false) {}

		/// \brief The move constructor.
		ScopeGuard(ScopeGuard&& rhs)
			:
			func_(std::move(rhs.func_)),
			dismiss_(rhs.dismiss_) {
			rhs.dismiss();
		}

		/// \brief The destructor.
		///
		/// \warning If the function exists, and has not been dismissed, execute it in the block catch(...) {}.
		~ScopeGuard() {
			if (!dismiss_ && func_ != nullptr) {
				func_();
			}
		}
		
		/// \brief If this function is manually called, func_ will not be called in the destructor.
		void dismiss() {
			dismiss_ = true;
		}

	private:
		ScopeGuard();
		ScopeGuard(const ScopeGuard&);
		ScopeGuard& operator=(const ScopeGuard&);

		///< \brief the function pointer
		///< \warning this function is responsible for cleanup from abnormal exit
		F func_;

		///< \brief the dismiss flag, "should the program execute func_?"
		bool dismiss_;
	};

	template <typename F>
	ScopeGuard<typename std::decay<F>::type> make_guard(F&& f) {
		return ScopeGuard<typename std::decay<F>::type>(std::forward<F>(f));
	}
}

#endif	// DJA_SCOPEGUARD_H_
