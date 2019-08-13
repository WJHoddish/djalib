#include <iostream>

#include "dja11/controller/delegate/delegate.h"

using namespace dja;

class A {
public:
	A(int data)
		:
		data_(data) {}

	int func(int data) {
		std::cout << "func: " << data_ + data << "\n";
		return data_ + data;
	}

	static int func_static(int data) {
		std::cout << "static func: " << data << "\n";
		return data;
	}

private:
	int data_;
};

int main(int argc, char* argv[]) {
	A a(5);
	Delegate<int, int> e;
	e += make_delegate(A::func_static);
	e += make_delegate(&a, &A::func);
	
	auto func_lambda = make_delegate(static_cast<int(*)(int)>(
		[](int data) {
			std::cout << "lambda: " << data << "\n";
			return data;
		}
	));
	e += func_lambda;

	// use a std::vector<...> to store multiple results
	auto vec = e(8);

	return 0;
}