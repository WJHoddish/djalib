#include <iostream>

#include "dja/core/objectcounter.h"

using namespace dja;

class A : public ObjectCounter<A> {
public:
	// implementations
};

int main(int argc, char* argv[]) {
	A a;

	std::cout << A::live();
	
	return 0;
}