#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is an object counter implemented by the crtp.
//

#ifndef DJA_OBJECTCOUNTER_H_
#define DJA_OBJECTCOUNTER_H_

namespace dja {
	/// \brief An derived-class object counter achieved by CRTP.
	template <typename T>
	class ObjectCounter {
	public:
		/// \brief Call this static function to know the number of existing objects of the derived class.
		static size_t live() {
			return ObjectCounter<T>::cnt_;
		}

	protected:
		/// \brief The constructor.
		ObjectCounter() {
			++ObjectCounter<T>::cnt_;
		}

		/// \brief The copy constructor.
		///
		/// During the copying process, the count number will be auto-incrementing.
		ObjectCounter(const ObjectCounter<T>&) {
			++ObjectCounter<T>::cnt_;
		}

		/// \brief The destructor.
		///
		/// \warning Please do NOT explicitly call the destructor in your project, 
		/// cause it will modify the value of counter, but not affect the existence of object.
		/// It can easily bring errors or lead to misjudgment while using the counter.
		~ObjectCounter() {
			--ObjectCounter<T>::cnt_;
		}

	private:
		///< \brief the counter
		static size_t cnt_;
	};

	template <typename T>
	size_t ObjectCounter<T>::cnt_ = 0;
}

#endif	// DJA_OBJECTCOUNTER_H_
