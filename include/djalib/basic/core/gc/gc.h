#pragma once

// Copyright (C) 2019 Jiaheng Wang. All Rights Reserved.
// This is a prototype garbage collector in cpp.
//

#ifndef GC_H_
#define GC_H_

#include <set>
#include <vector>

#include "gc_base.h"

namespace dja {
class GarbageCollector {
  typedef std::set<GCObject*> ObjectSet;

 public:
  /// \brief To perform garbage collection.
  void collect();

  /// \brief Traverse all heap objects, then
  ///
  /// 1. Unmark live objects.
  /// 2. Destroy the unreferenced ones.
  ///
  /// \attention One thing that makes the gc effective is gc has the right to
  /// unmark all pointers if they haven't been registered to the root.
  void sweep();

  void insertRoot(GCObject* ptr);

  void removeRoot(GCObject* ptr);

  /// \brief Add a heap allocated object to the collector.
  void insertObject(GCObject* ptr);

  /// \brief Remove the object pointer.
  void removeObject(GCObject* ptr);

  /// \brief Number of live objects in the heap.
  size_t live();

  /// \brief Show the heap details.
  void heap();

  ///< \brief the global garbage collector object
  static GarbageCollector GC;

 private:
  ///< \brief a collection of all "active" heap objects
  ObjectSet heap_;

  ///< \brief a collection of objects that are scanned for garbage
  ObjectSet roots_;
};
}  // namespace dja

#endif