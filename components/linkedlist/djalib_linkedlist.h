#pragma once
// the imitation of STL list<...>
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>

namespace djalib
{
	template<typename T>
	class Linkedlist
	{
		class Node 
		{
		public:
			T _data;
			Node* front;
			Node* next;

		public:
			Node(const T& data) :
				_data(data), 
				front(nullptr), next(nullptr) {
				// ATTENTION: here only call the "copy constructor"!
				// as using ") : xxx(xxx), xxx(xxx) {}".
			}
			~Node() {
				std::cout << "(node) destructor." << "\n";
			}
		};

	public:
		class Iterator
		{
			Node* head;

		public:
			Iterator() :
				head(nullptr) {}
			Iterator(Node*& p) :
				head(p) {}
			Iterator(Iterator& itr) :
				head(itr.head) {}

		public:
			// pre++:
			Iterator operator ++() {
				head = head->next;
				return *this;
			}
			// after++:
			Iterator operator ++(int) {
				Iterator temp(*this);
				head = head->next;
				return temp;
			}

			// get value (*...):
			friend const T& operator *(Iterator& it) {
				std::cout 
					<< "use iterator*" << "\t" 
					<< "address: " << it.head << "\n";
				return 
					it.head->_data;
			}

			friend bool operator !=(Iterator& it, Iterator& it1) {
				if (it.head != it1.head)
					return true;
				return false;
			}
		};

	private:
		Node* head;
		Node* tail;
		bool New_n(Node*& p, const T& data) {
			// private func: allocate heap memory.
			// attention: vars "head" & "tail" are required to point at heap! 
			p = new Node(data);
			return 
				true;
		}

	public:
		Linkedlist();
		~Linkedlist();

	public:
		void push_back(const T& n_data);
		void push_front(const T& n_data);

		// delete a specified target.
		bool Remove(const T& a);

		// find a specified target.
		Node* Search(const T& a);

		// destroy all, release memory.
		bool Destroy();

	public:
		Iterator begin() { return Iterator(head); }
		Iterator end() { return Iterator(tail->next); }

		// test func, only available for data T supported by compiler!
		void show() {
			Node* p = head;
			if (!p)
				return;
			while (p) {
				std::cout 
					<< p->_data << "\n";
				p = p->next;
			}
		}
	};

}

template<typename T>
djalib::Linkedlist<T>::Linkedlist() {
	head = nullptr;
	tail = head;
}

template<typename T>
void djalib::Linkedlist<T>::push_back(const T& n_data) {
	Node* temp;
	New_n(temp, n_data);
	if (!head) {
		// no element.
		head = temp;
		tail = temp;
		return;
	}
	else {
		// not emepty.
		tail->next = temp;
		temp->front = tail;
		tail = temp;
		return;
	}
}

template<typename T>
void djalib::Linkedlist<T>::push_front(const T& n_data) {
	Node *temp;
	New_n(temp, n_data);
	if (!tail) {
		// no element.
		head = temp;
		tail = temp;
		return;
	}
	else {
		// not emepty.
		head->front = temp; // element before current head becomes temp.
		temp->next = head;	// 
		head = temp;		// renew the position of 'head'.
		return;
		// who's my front? who's my next?
	}
}

template<typename T>
bool djalib::Linkedlist<T>::Remove(const T& a) {
	// get the pointer we want to delete.
	Node* target = Search(a);		
	if (!target)
		return false;
	else {
		// target is found!
		if (target == head) {
			// is head.
			head = target->next;
			head->front = nullptr;
			delete target;
			return true;
		}
		else if (target == tail) {
			// is tail.
			tail = target->front;
			tail->next = nullptr;
			delete target;
			return true;
		}
		else {
			// in the middle.
			Node* temp = target;
			target->front->next = target->next;
			target->next->front = target->front;
			delete temp;
			return true;
		}
	}
}

template<typename T>
typename djalib::Linkedlist<T>::Node* djalib::Linkedlist<T>::Search(const T& a) {
	if (!head)
		return nullptr;
	else {
		// not empty.
		for (Node* cursor = head; cursor; cursor = cursor->next) {
			if (cursor->_data == a)
				return cursor;
		}
		// not found.
		return nullptr;
	}
}

template<typename T>
bool djalib::Linkedlist<T>::Destroy() {
	// delete all heap memory, be called in ~Linkedlist():
	Node* temp = head;
	if (!temp) {
		// no element...
		return true;
	}
	else {
		for (Node* p;;) {
			p = temp;
			temp = temp->next;
			delete p;
			if (!temp) {
				head = nullptr;
				tail = nullptr;
				break;
			}
		}
		return true;
	}
}

template<typename T>
djalib::Linkedlist<T>::~Linkedlist() {
	// delete all heap memory:
	Destroy();
}

#endif
