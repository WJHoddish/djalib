#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a non-copyable class, any copy behaviour of its derived classes is prohibited.
//

#ifndef DJA_NONCOPYABLE_H_
#define DJA_NONCOPYABLE_H_

namespace dja {
	/// \brief Copy behaviours of its derived classes is prohibited.
	class NonCopyable {
	public:
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
		NonCopyable() = default;
	};
}

#endif	// DJA_NONCOPYABLE_H_
