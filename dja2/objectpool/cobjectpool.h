#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a simple object pool.
//

/// \brief This is a simple object pool.
///
/// This is an object pool in cpp, which uses char array to store objects on the heap only.
/// This is also a compile-time object (memory) pool.
/// By using macro definitions, you just need to put two macro in the class declaration and definition respectively.
/// This class is which you intend to organise its object by a pool,
/// and it will be attached by a CObjectPool as a static class member.
/// What's more, two functions: "create" and "clear" are attached for applying and releasing memory.
/// Meanwhile, two functions: "init" and "destroy" is required to be members for the target class.
/// "create" has a variable number of arguments,
/// "clear" will return the memory space back to the pool.
/// Thus, you can set any arguments for "init".
/// In "destroy", you have a chance to delete heap members, however, it violates the design of the object pool.
/// The pool is a big chunk of memory on the heap, where a free node is regarded as the head or entrance of the pool.
/// Every time you apply a new object, its nature is to return the address of that free node,
/// Meanwhile, the "create" will call "init" and overwrite that chunk of memory.
///
/// \attention There is one thing you need to pay attention.
/// Once you call the function "clear", please set your pointer as nullptr,
/// otherwise you may access a chunk of "released" memory though this "wild pointer".
///

#ifndef DJA_COBJECTPOOL_H_
#define DJA_COBJECTPOOL_H_

namespace dja {
template <typename T, int chunk_size = 9>
class CObjectPool {
 public:
  /// \brief The constructor.
  CObjectPool() : free_node_(nullptr), head_block_(nullptr) {}

  /// \brief The destructor.
  ///
  /// \attention Free all memory in the list.
  ~CObjectPool() {
    ObjectBlock* cursor;
    while (head_block_) {
      cursor = head_block_->next_;
      {
        delete head_block_;
        head_block_ = cursor;
      }
    }
  }

  /// \brief Allocate a new memory chunk.
  void* allocateChunk() {
    if (!free_node_) {
      ObjectBlock* new_block = new ObjectBlock;
      new_block->next_ = head_block_;
      new_block->data_[0].next_ = nullptr;
      for (int i = 1; i < chunk_size; ++i) {
        ObjectNode* temp = &(new_block->data_[i - 1]);
        (new_block->data_[i]).next_ = temp;
      }
      free_node_ = &(new_block->data_[chunk_size - 1]);
      head_block_ = new_block;
    }
    ObjectNode* new_node = free_node_;
    free_node_ = free_node_->next_;
    return new_node->item_;
  }

  /// \brief Push the free memory back to list.
  ///
  /// \attention Released node which is inserted to the head of spare nodes.
  void freeChunk(void* p) {
    char* temp = static_cast<char*>(p);
    { temp -= sizeof(ObjectNode*); }
    ObjectNode* node = static_cast<ObjectNode*>(static_cast<void*>(temp));
    node->next_ = free_node_;
    free_node_ = node;
  }

  /// \brief Pass a function, functor, lambda expression to it and apply to all
  /// objects in the pool.
  template <typename F>
  void mapAll(F& fn) const {
    for (ObjectBlock* cursor = head_block_; cursor; cursor = cursor->next_) {
      for (int i = 0; i < chunk_size; ++i) {
        T* temp = static_cast<T*>(static_cast<void*>(cursor->data_[i].item_));
        fn(*temp);
      }
    }
  }

 private:
  class ObjectNode {
    /// \brief The constructor.
    ObjectNode() : next_(nullptr) { std::memset(item_, 0, sizeof(T)); }

    friend class CObjectPool<T, chunk_size>;

    ObjectNode* next_;
    char item_[sizeof(T)];
  };

  class ObjectBlock {
    /// \brief The constructor.
    ObjectBlock() : next_(nullptr) {}

    friend class CObjectPool<T, chunk_size>;

    ObjectBlock* next_;
    ObjectNode data_[chunk_size];
  };

  ///< \brief the first free node and the head block
  ObjectNode* free_node_;
  ///< \brief there is a list linking each block
  ObjectBlock* head_block_;
};

#define COBJECTPOOL_VAR_DECLARE(class_name) \
 public:                                    \
  static CObjectPool<class_name> pool;

#define COBJECTPOOL_FUNC_CREATE(class_name)                         \
 public:                                                            \
  template <typename... Args>                                       \
  static class_name* create(Args&&... args) {                       \
    class_name* p = static_cast<class_name*>(pool.allocateChunk()); \
    p->init(std::forward<Args>(args)...);                           \
    return p;                                                       \
  }                                                                 \
                                                                    \
 private:

#define COBJECTPOOL_FUNC_CLEAR(class_name)          \
 public:                                            \
  void clear() {                                    \
    class_name* p = static_cast<class_name*>(this); \
    p->destroy();                                   \
    pool.freeChunk(this);                           \
  }                                                 \
                                                    \
 private:

#define COBJECTPOOL_HEAPONLY(class_name) \
 private:                                \
  ~class_name() {}

#define COBJECTPOOL_INCLASS(class_name) \
  COBJECTPOOL_VAR_DECLARE(class_name)   \
  COBJECTPOOL_FUNC_CREATE(class_name)   \
  COBJECTPOOL_FUNC_CLEAR(class_name)    \
  COBJECTPOOL_HEAPONLY(class_name)

#define COBJECTPOOL_EXCLASS(class_name) \
  CObjectPool<class_name> class_name::pool;

}  // namespace dja

#endif
