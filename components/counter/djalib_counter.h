#pragma once
#ifndef _counter_H_
#define _counter_H_
// a counter for those extremly large numbers.

#include <assert.h>
#include <malloc.h>
#include <iostream>

namespace djalib
{
	const int COUNTER_SYSTEM = 1024;

	class counter
	{
		class List
		{
			class Unit
			{
				// the linked-list node.
				int _count;
				Unit* _next;

			public:
				friend class List;

				// constructor:
				Unit() :
					_count(0), 
					_next(nullptr) {
					// pass.
				}
				~Unit() {
					// pass.
				}

			public:
				int magnitude() {
					return this->_count;
				}

			public:
				void display() {
					std::cout 
						<< "node: " << this->_count << "\n";
				}
			};

			// the linked-list.
			size_t		_size;
			Unit*		head;
			Unit*		tail;

			void init() {
				_size = 2;
				head = new Unit();
				tail = new Unit();
				head->_next = tail;
			}
			void destroy() {
				_size = 0;
				Unit* temp = head->_next;
				Unit* tempNext = temp->_next;
				while (temp != tail) {
					delete temp;
					temp = tempNext;
					tempNext = temp->_next;
				}
				delete head;
				delete tail;
			}

		public:
			List() {
				init();
			}
			List(int num) {
				init();
				*this += (num);
			}

			~List() {
				std::cout 
					<< "(List) destructor!" << "\n";
				destroy();
			}

		public:
			size_t size() const {
				return this->_size;
			}
			Unit* getHead() {
				return this->head;
			}

		protected:
			void insertAtTail() {
				this->tail->_next = new Unit();
				this->tail = tail->_next;
				(this->_size)++;
			}

		public:
			void operator +=(const int num) {
				Unit* cursor = this->head;
				nodeIncrease(cursor, num);
			}
			void nodeIncrease(Unit* cursor, const int num) {
				assert(cursor != nullptr);
				int percent 
					= ((num % COUNTER_SYSTEM) + (cursor->_count)) % COUNTER_SYSTEM;
				int slash 
					= ((num % COUNTER_SYSTEM) + (cursor->_count)) / COUNTER_SYSTEM + num / COUNTER_SYSTEM;
				cursor->_count = percent;
				if (slash > 0) {
					// new position:
					if (cursor->_next == nullptr) {
						assert(cursor == this->tail);
						this->insertAtTail();
					}
					nodeIncrease(cursor->_next, slash);	// recursion.
				}
				else
					return;
			}

			bool operator >(const List& ref) {
				if (
					this->_size > ref._size) {
					return true;
				}
				else if (
					this->_size < ref._size) {
					return false;
				}
				else {
					assert(this->_size == ref._size);
					bool result;
					Unit* cursor_self = this->head;
					Unit* cursor_ref = ref.head;
					for (int i = 0; i < (this->_size); ++i) {
						if (cursor_self->magnitude() != cursor_ref->magnitude())
							result = (cursor_self->_count > cursor_ref->_count);
						cursor_self = cursor_self->_next;
						cursor_ref = cursor_ref->_next;
					}
					return result;
				}
			}

		public:
			void display() {
				// display the whole list:
				std::cout 
					<< "LSB" << "->";
				for (Unit* cursor = head;; cursor = cursor->_next) {
					std::cout << cursor->_count << "->";
					if (cursor == tail) {
						std::cout << "MSB";
						break;
					}
				}
			}
		};

		// the counter.
		List* _list;		// data.
		int* ref_count;		// reference count.

		void destroy() {
			assert(!(*ref_count));
			delete _list;	// will show the list has been destructed.
			delete ref_count;
			_list = nullptr;
			ref_count = nullptr;
		}

	public:
		counter(int num = 0) :
			_list(new List(num)) {
			try {
				ref_count
					= new int(1);
			}
			catch (...) {
				{
					delete _list;
					_list = nullptr;
				}
				ref_count = nullptr;
				std::cout
					<< "(counter) memory allocation failed." << "\n";
				std::system("pause");
				exit(1);
			}
		}
		counter(const counter& ref) {
			this->_list = ref._list;
			this->ref_count = ref.ref_count;
			++(*ref_count);
		}
		~counter() {
			if (--(*ref_count) == 0) {
				destroy();
			}
		}

		counter& operator =(const counter& rhs) {
			// prevent self-assignment!
			++(*rhs.ref_count);

			if (--(*ref_count) == 0) {
				destroy();
			}

			this->_list = rhs._list;
			this->ref_count = rhs.ref_count;

			return *this;
		}

	public:
		void operator +=(const int num) const {
			(*_list) += num;
		}

		// comparison:
		bool operator >(const counter& ref) {
			return
				(*_list) > *(ref._list);
		}

	public:
		void display() const {
			_list->display();
			std::cout 
				<< "\n";
		}
	};
}

#endif
