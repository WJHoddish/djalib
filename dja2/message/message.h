#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a message box.
//

#ifndef DJA_MESSAGE_H_
#define DJA_MESSAGE_H_

#include <string>
#include <iostream>

#include "../objectpool/cobjectpool.h"

namespace dja {
	class Message {
		friend std::ostream& operator <<(std::ostream& os, Message& src);

		/// \brief The max size of the string.
		enum { STRING_SIZE = 64 };

		/// \brief Initiate the message string.
		///
		/// \attention Usage: Message* p_str = Message::create("hello, world");
		void init(const char src[]) {
			std::memset(msg_, '\0', STRING_SIZE);
			for (int i = 0; i < STRING_SIZE; ++i) {
				msg_[i] = src[i];
				if (src[i] == '\0') { break; }
			}
		}

		/// \brief Erase the message string.
		///
		/// \attention Usage: p_str->clear();
		void destroy() {
			std::memset(msg_, '\0', STRING_SIZE);
		}

		char msg_[STRING_SIZE];

		COBJECTPOOL_INCLASS(Message)
	};
}

#endif	// DJA_MESSAGE_H_
