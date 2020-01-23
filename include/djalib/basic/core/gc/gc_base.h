#pragma once

// Copyright (C) 2019 Jiaheng Wang. All Rights Reserved.
// This is a prototype garbage collector in cpp.
//

#ifndef DJA_GC_BASE_H_
#define DJA_GC_BASE_H_

namespace dja
{
class GarbageCollector;

/// \brief The base class for all classes that are tracked by the garbage
/// collector.
///
/// \attention Using the mark and sweep algorithm.
class GCObject
{
  friend class GarbageCollector;

public:
  GCObject();

  GCObject(GCObject const &);

  /// \brief Mark the object and all its children as "live".
  virtual void mark() final;

  /// \brief To mark all member gc-attached variables.
  ///
  /// \warning You must override this function in derived classes, calling
  /// mark() on those objects "referenced by" this object.
  virtual void markChildren() = 0;

  ///< \brief For mark and sweep algorithm.
  /// When a GC occurs all live objects are traversed and marked_ is set to
  /// true. This is followed by the sweep phase where all unmarked objects are
  /// deleted.
  bool marked_;

protected:
  /// \brief The destructor.
  ///
  /// Will remove the focused pointer from the garbage collector.
  virtual ~GCObject();

  /// \brief Clean up heap memory (in derived classes).
  ///
  /// \attention As a pure virtual function, it should be overrided in derived
  /// classes. Since the gc-attached is forced to be heap-only object, and
  /// their destructors are declared as private members. If they are acting as
  /// member variables in gc-attached classes, you don't need and you also
  /// cannot clear them by using reserved word delete.
  virtual void destroy() = 0;
};
} // namespace dja

#define GC_USE \
public         \
  dja::GCObject

#define GC_HEAP_ONLY(class_name)                         \
private:                                                 \
  /*\brief Automatically call the func to release heap*/ \
  ~class_name() { destroy(); }

#define GC_INCLASS(class_name) GC_HEAP_ONLY(class_name)

#endif