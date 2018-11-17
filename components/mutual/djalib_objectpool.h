#pragma once
#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <iomanip>
#include <cassert>
#include <iostream>

namespace djalib
{
	template <typename T, int capacity>
	class Objpool
	{
		class Node
		{
			Node*	_next;
			char	_item[sizeof(T)] = { 0 };
			
		public:
			friend class Objpool<T, capacity>;
		};

		class Block
		{
			Block*	_next;
			Node	_data[capacity];

		public:
			friend class Objpool<T, capacity>;
		};

		Node*	freeNode;		// every time a new object will be allocated to this address.
		Block*	headBlock;		// a memory block (linked-list).

	public:
		Objpool() :
			freeNode(nullptr),
			headBlock(nullptr) {
			assert(capacity);
		}
		~Objpool() {
			Block* cursor;
			while (headBlock) {
				cursor = headBlock->_next;
				delete headBlock;
				headBlock = cursor;
			}
		}

	public:
		void* Malloc(void) {
			// hand in mem space which has been already allocated:
			if (!freeNode) {
				// no spare node:
				Block* newBlock = new Block;
				newBlock->_next = headBlock;			// set: "the first free node of the memblock" is:
				newBlock->_data[0]._next = nullptr;		// "the last node of 'free node linked-list'".
				for (int i = 1; i < capacity; ++i)
					newBlock->_data[i]._next = &(newBlock->_data[i - 1]);
				freeNode = &(newBlock->_data[capacity - 1]);
				headBlock = newBlock;
			}
			// return the first node of "free node list":
			Node* newNode = freeNode;
			freeNode = freeNode->_next;
			return newNode->_item;
		}
		void Free(void* p) {
			// released node which is inserted to the head of spare nodes:
			char* temp = static_cast<char*>(p);
			{
				temp -= sizeof(Node*);	
				// the sequence of instance vars arranged in a class is significant!
				// pay attention when you are cautiously moving the pointer position!
			}
			Node* _node = (Node*)temp;
			_node->_next = freeNode;
			freeNode = _node;
		}

	public:
		void display() {
			for (Block* cursor = headBlock; cursor; cursor = cursor->_next) {
				for (int i = 0; i < capacity; ++i) {
					std::cout << i + 1 << ":\t";
					T* temp = static_cast<T*>(static_cast<void*>(cursor->_data[i]._item));
					{
						std::cout
							<< "address: " << static_cast<void*>(temp) << "\t"
							<< (*temp) << "\n";
						// the target class should have overload operator: "<<", 
						// for every "pool-needed" class!.
					}
				}
			}
		}
	};

	//------------------------------
	//------------------------------
#define OBJPOOL_VAR_DECLARE(name) \
	public: \
		static Objpool<name, 9> pool;
#define OBJPOOL_VAR_INIT(name) \
		Objpool<name, 9> name::pool;

#define OBJPOOL_FUN_STACKONLY(name) \
	private: \
		name(){} \
		~name(){}

#define OBJPOOL_FUN_CREATE(name) \
	public: \
		static name* Create() { \
			name* p = static_cast<name*>(pool.Malloc()); \
			p->initial(/* please set a default value for all instance vars in class! */); \
			return p; \
		}
#define OBJPOOL_FUN_DESTROY(name) \
	public: \
		void Destory() { \
			static_cast<name*>(this)->release(/* please release all heap memory here! */); \
			pool.Free(this); \
		}

#define OBJPOOL_FUN_DISPLAY_DECLARE(name) \
	public: \
		friend std::ostream& operator <<(std::ostream& os, name& obj);
#define OBJPOOL_FUN_DISPLAY_INIT(name) \
		std::ostream& operator <<(std::ostream& os, name& obj) { \
			obj.display(/* please set a proper method to show contents of this class! */); \
			return os; \
		}

	//------------------------------
	//------------------------------
#define OBJPOOL_INCLASS(name) \
	OBJPOOL_VAR_DECLARE(name) \
	OBJPOOL_FUN_STACKONLY(name) \
	OBJPOOL_FUN_CREATE(name) \
	OBJPOOL_FUN_DESTROY(name) \
	OBJPOOL_FUN_DISPLAY_DECLARE(name)
	
#define OBJPOOL_EXCLASS(name) \
	OBJPOOL_VAR_INIT(name) \
	OBJPOOL_FUN_DISPLAY_INIT(name)

}

#endif
