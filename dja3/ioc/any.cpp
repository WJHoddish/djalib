// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a cpp implementation meta class using RTTI for type erase.
//

#include "any.h"

namespace dja {
	Any::Any()
		:
		type_(std::type_index(typeid(void))) {}

	Any::Any(const Any& src)
		:
		ptr_(src.clone()),
		type_(src.type_) {}

	Any::Any(Any&& src) noexcept
		:
		ptr_(std::move(src.ptr_)),
		type_(src.type_) {}

	bool Any::isNull() const {
		return !bool(ptr_);
	}

	Any& Any::operator=(const Any& src) {
		if (ptr_ != src.ptr_) {
			ptr_ = src.clone();
			type_ = src.type_;
		}
		return *this;
	}

	Any& Any::operator=(Any&& src) noexcept {
		if (ptr_ != src.ptr_) {
			ptr_ = std::move(src.ptr_);
			type_ = src.type_;
		}
		return *this;
	}
}
