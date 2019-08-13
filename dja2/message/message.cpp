// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a message box.
//

#include "message.h"

namespace dja {
	std::ostream& operator <<(std::ostream& os, Message& src) {
		os << src.msg_;
		return os;
	}

	COBJECTPOOL_EXCLASS(Message)
}
