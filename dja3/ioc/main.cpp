#include "ioc.h"

using namespace dja;

class A {
public:
	A() {
		std::cout << "A" << "\n";
	}

	virtual ~A() {}
	virtual void fun() const = 0;
};

class B : public A {
public:
	B(int i, float f) {
		std::cout << "B" << "\n";
	};

	void fun() const {
		std::cout << "hello, world" << "\n";
	}
};

int main(int argc, char* argv[])
{
	Ioc ioc;
	ioc.typeRegister<A, B, int, double>("C");

	{
		auto obj = ioc.resolveShared<A>("C", 1, 2.0);
		obj->fun();
	}

	std::system("pause");

	{
		counted_ptr<B> ptr(new B(1, 2.0));
	}

	return 0;
}