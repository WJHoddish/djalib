// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a timer.
//

#include "dja/tool/timer.h"

namespace dja {
	Timer::Timer()
		:
		begin_(std::chrono::high_resolution_clock::now()) {}

	bool Timer::reset() {
		begin_ = std::chrono::high_resolution_clock::now();
	}

	long long Timer::elapsed() const {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_).count();
	}
}