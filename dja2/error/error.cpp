// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is an self-defined cpp exception class.
//

#include "error.h"

#include <sstream>
#include <iostream>

namespace dja {
	Exception::Exception(std::string msg)
		:
		kind_("error"),
		msg_(msg) {}

	void Exception::dump() const {
		dump(std::cerr);
	}

	void Exception::dump(std::ostream& out) const {
		out << "\n";
		out << "Djalib Error: ";
		if (!msg_.empty()) {
			out << msg_;
		}
		if (hasStackTrace()) {
			out << "\n";
			out << getStackTrace();
		}
		out.flush();
	}

	std::string Exception::getKind() const {
		return kind_;
	}

	std::string Exception::getMessage() const {
		return msg_;
	}

	bool Exception::hasStackTrace() const {
		return !stack_trace_.empty();
	}

	std::string Exception::getStackTrace() const {
		return stack_trace_;
	}

	void Exception::setKind(const std::string& str) {
		kind_ = str;
	}

	void Exception::setStackTrace(const std::string& str) {
		stack_trace_ = str;
	}

	/// \brief The std style error announcement.
	const char* Exception::what() const noexcept {
		return ("Djalib Error: " + msg_).c_str();
	}

	std::ostream& operator <<(std::ostream& out, const Exception& e) {
		out << "Djalib Error: " << e.what();
		std::string stack = e.getStackTrace();
		if (!stack.empty()) {
			out << "Stack trace:" << std::endl;
			out << stack;
			out.flush();
		}
		return out;
	}

	void error(const std::string& str) {
		throw Exception(str);
	}
}
