// Copyright (C) 2009 Jiaheng Wang. All Rights Reserved.
// This is a prototype garbage collector in cpp.
//

#include "gc.h"

#include <iostream>

namespace dja
{
GarbageCollector GarbageCollector::GC;

void GarbageCollector::collect()
{
  // root means all registered pointer will be "marked" every time.
  for (ObjectSet::iterator it = roots_.begin(); it != roots_.end(); ++it)
  {
    // mark root objects
    (*it)->mark();
  }
  sweep();
}

void GarbageCollector::sweep()
{
  size_t live = 0, dead = 0, total = 0;
  // unmark all live objects
  std::vector<ObjectSet::iterator> erase;
  for (ObjectSet::iterator it = heap_.begin(); it != heap_.end(); ++it)
  {
    total++;
    // traverse the heap
    GCObject *p = *it;
    if (p->marked_)
    {
      ++live;
      // marked objects are those who are still alive
      p->marked_ = false;
    }
    else
    {
      // if it's unmarked (default status), push into the erase list
      erase.push_back(it);
    }
  }
  // destroy the unreferenced ones
  dead = erase.size();
  for (std::vector<ObjectSet::iterator>::iterator it = erase.begin();
       it != erase.end(); ++it)
  {
    // traverse the erase list
    GCObject *p = **it;
    {
      delete p;
    }
  }
}

void GarbageCollector::insertRoot(GCObject *ptr) { roots_.insert(ptr); }

void GarbageCollector::removeRoot(GCObject *ptr) { roots_.erase(ptr); }

void GarbageCollector::insertObject(GCObject *ptr) { heap_.insert(ptr); }

void GarbageCollector::removeObject(GCObject *ptr) { heap_.erase(ptr); }

size_t GarbageCollector::live() { return heap_.size(); }

void GarbageCollector::heap()
{
  if (!heap_.empty())
  {
    for (ObjectSet::iterator it = heap_.begin(); it != heap_.end(); ++it)
    {
      std::cout << static_cast<void *>(*it) << std::endl;
    }
  }
}
} // namespace dja

namespace dja
{
GCObject::GCObject() : marked_(false)
{
  // record the object pointer
  GarbageCollector::GC.insertObject(this);
}

GCObject::GCObject(GCObject const &) : marked_(false)
{
  // record the object pointer
  GarbageCollector::GC.insertObject(this);
}

GCObject::~GCObject()
{
  // remove recorded pointer
  GarbageCollector::GC.removeRoot(this);
  GarbageCollector::GC.removeObject(this);
}

void GCObject::mark()
{
  if (!marked_)
  {
    marked_ = true;
    markChildren();
  }
}

void GCObject::markChildren() {}
} // namespace dja