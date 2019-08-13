#include <iostream>

#include "message/message.h"
#include "counter/counter.h"

void display(dja::Message& msg) {
	std::cout << msg << "\n";
}

int main(int argc, char* argv[]) {
	{

	}

	{
		using namespace dja;
		std::string str("djalib");
		Message* msg = Message::create(str.c_str());
		Message::pool.mapAll(display);
	}

	const int n = 20;
	{
		using namespace dja;
		Message* arr[n];
		for (int i = 0; i < n; ++i) {
			arr[i] = Message::create("hello, world");
		}
		Message::pool.mapAll(display);

		for (int i = 5; i < 15; ++i) {
			arr[i]->clear();
		}
		Message::pool.mapAll(display);

		for (int i = 5; i < 10; ++i) {
			arr[i] = Message::create("new message");
		}
		Message::pool.mapAll(display);
	}

	{
		dja::Counter cnt(16500);
		std::cout << cnt << "\n";
	}
	return 0;
}
