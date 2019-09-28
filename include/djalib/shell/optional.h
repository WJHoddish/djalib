#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// 
//

#ifndef DJA_OPTIONAL_H_
#define DJA_OPTIONAL_H_

#include <utility>
#include <stdexcept>
#include <type_traits>

namespace dja {
	template <typename T>
	class Optional {
		using Type = typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type;
	public:
		/// \brief The constructor.
		///
		/// \warning As you can see, the aligned memory which is got for the type-T object, 
		/// is left empty in the default constructor. 
		/// This design prevents the invocation of the type-T default constructor,
		/// achieving the function of what we call "optional".
		Optional()
			:
			init_(false) {
		}

		Optional(const T& ref)
			:
			init_(false) {
			init(ref);
		}

		/// \brief The copy constructor.
		Optional(const Optional& src)
			:
			init_(false) {
			if (src.isInit()) {
				assign(src);
			}
		}

		/// \brief The destructor.
		~Optional() {
			destroy();
		}

		Optional& operator =(const Optional& src) {
			if (this != &src) {
				assign(src);
			}
			return *this;
		}

		/// \brief Get the type-T object if the Optional has been initialised.
		///
		/// \warning This library requires a stadard exception class to adapt all kinds of exceptions.
		const T& operator *() const {
			if (isInit()) {
				return *reinterpret_cast<const T*>(&data_);
			}
			throw std::logic_error{ "djalib error: try to use an uninitialised optional" };
		}

		T& operator *() {
			if (isInit()) {
				return *reinterpret_cast<T*>(&data_);
			}
			throw std::logic_error{ "djalib error: try to use an uninitialised optional" };
		}

		const T* operator ->() const {
			return &operator*();
		}

		T* operator ->() {
			return &operator*();
		}

		/// \brief Provide a way of using "!" to define the initialisation status.
		explicit operator bool() const {
			return isInit();
		}

		/// \brief ==.
		///
		/// \warning This method requires the == operator is oveloaded in type-T.
		bool operator ==(const Optional<T>& rhs) const {
			return (!bool(*this)) != (!rhs) ? false : (!bool(*this) ? true : (*(*this)) == (*rhs));
		}

		bool operator !=(const Optional<T>& rhs) {
			return !(*this == (rhs));
		}

		bool isInit() const {
			return init_; 
		}

		template <class... Args>
		void emplace(Args&& ... args) {
			destroy();
			init(std::forward<Args>(args)...);
		}

	private:
		/// \brief Create the internal data object.
		///
		/// It will be used when the container is constructed by a specified value.
		template <class... Args>
		void init(Args&& ... args) {
			new (&data_) T(std::forward<Args>(args)...);
			init_ = true;
		}

		void assign(const Optional& src) {
			if (src.isInit()) {
				copy(src.data_);
				init_ = true;
			}
			else {
				destroy();
			}
		}

		/// \brief Reset the object status.
		///
		/// It explicitly calls the type-T destructor to release heap memory.
		void destroy() {
			if (init_) {
				init_ = false;
				reinterpret_cast<T&>(data_).~T();
			}
		}

		/// \brief Copy from another real data.
		///
		/// If the source object is initialised, this method will be called to generate the same object for copying.
		void copy(const Type& val) {
			destroy();
			new (&data_) T(reinterpret_cast<const T&>(val));
		}

		///< \brief the type-T data after aligned in memory
		///
		/// As a part of stack memory lives in the Optional class, it will be recycled automatically.
		Type data_;

		///< \brief the flag of initialisation
		bool init_;
	};
}

#endif
