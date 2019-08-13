
#include "dja11/controller/messagebus/messagebus.h"

using namespace dja;

///< \brief The message bus commander.
MessageBus bus;

class Subject {
public:
	/// \brief A subject object is responsible for spreading the message.
	static void send(int a, const std::string& topic) {
		// <return_type, arguments_list>
		bus.send<void, int>(std::move(a), topic);
	}
};

class Listener {
public:
	/// \brief The constructor.
	///
	/// \attention I recommend you to register a lambda expression under a certain topic with a specified function type.
	/// This lambda expression usually links to a member function,
	/// which implies that this member function will be executed when a message is broadcasted.
	Listener(const std::string& topic)
		:
		data_(0) {
		bus.attach([this](int data) { change(data); }, topic);
	}

	/// \brief Member functions.
	void change(int data) {
		data_ = data;
		std::cout << "data member has been changed." << "\n";
	}

	void display() const {
		std::cout << "data member: " << data_ << "\n";
	}

	int data_;
};

int main(int argc, char* argv[]) {
	std::string topic("topic");

	Listener listener(topic);
	{
		listener.display();
	}
	{
		Subject::send(3, topic);
		listener.display();
	}

	// you can remove a message like this.
	bus.remove<void, int>(topic);

	Subject::send(5, topic);

	return 0;
}