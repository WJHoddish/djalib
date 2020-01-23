#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// The reflection register.
//

#ifndef DJA_REFLECTION_REGISTER_H_
#define DJA_REFLECTION_REGISTER_H_

#include <map>
#include <string>
#include <typeinfo>

namespace dja
{
/// \brief Using template to generate a register for each base class.
template <typename T>
class ClassRegister
{
public:
  typedef T *(*Constructor)(void);
  typedef std::map<std::string, Constructor> ClassMap;

  ClassRegister() {}

  /// \brief Add the constructor of new classes.
  void registerClass(const std::string class_name, Constructor constructor)
  {
    typename ClassMap::iterator it = constructor_map_.find(class_name);
    if (it != constructor_map_.end())
    {
      // TODO(Jiaheng Wang): The class name you want to register already exists,
      // need to add the djalib-style exception.
      return;
    }
    constructor_map_[class_name] = constructor;
  }

  /// \brief Construct objects according to the class name.
  T *createObject(const std::string class_name) const
  {
    typename ClassMap::const_iterator it = constructor_map_.find(class_name);
    if (it == constructor_map_.end())
    {
      // class name not found
      return nullptr;
    }
    return (*(it->second))();
  }

private:
  ClassMap constructor_map_;
};

/// \brief Global use, to store the register objects for each base class.
template <typename T>
ClassRegister<T> &getRegister()
{
  static ClassRegister<T> class_register;
  return class_register;
}

/// \brief The constructor for each class.
///
/// \param T The type of base.
/// \param U The type of derived class.
/// \return The pointer to the base type.
template <typename T, typename U>
T *newObject()
{
  return new U();
}
} // namespace dja

#endif
