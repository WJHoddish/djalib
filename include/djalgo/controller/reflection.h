#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// Implement reflection in cpp using RTTI.
//

#ifndef DJA_REFLECTION_H_
#define DJA_REFLECTION_H_

#include <typeinfo>

#include "reflection_register.h"

namespace dja
{
class Reflection
{
public:
  /// \brief Using RTTI to solve the class name.
  ///
  /// \param T The type of base.
  /// \param U The type of derived class.
  template <typename T, typename U>
  static auto registerClass() ->
      typename std::enable_if<std::is_base_of<T, U>::value>::type
  {
    std::string class_name(typeid(U).name());
    // it's necessary to eliminate the "class " an get a sub-string
    getRegister<T>().registerClass(class_name.substr(6, class_name.size()),
                                   newObject<T, U>);
  }

  /// \brief Using the class name to summon a base pointer.
  template <typename T, typename... Args>
  static auto createObject(const std::string class_name, Args &&... args) -> T *
  {
    return getRegister<T>().createObject(class_name);
  }
};

/// \brief Create a helper for reflection classes, register when constructing.
///
/// Implement reflection in cpp by keeping a global variable.
template <typename T>
class ClassRegisterHelper
{
  typedef typename ClassRegister<T>::Constructor Constructor;

public:
  /// \brief The constructor.
  ClassRegisterHelper(const std::string class_name, Constructor constructor)
  {
    getRegister<T>().registerClass(class_name, constructor);
  }

  ~ClassRegisterHelper() {}
};

} // namespace dja

/// \brief The macro for reflection class's registration.
///
/// The name of base class and derived class are needed.
/// Its nature is to make a global static object that register your target
/// class while constructing.
#define REFLECTION_REGISTER_CLASS(base_class_name, sub_class_name) \
  static dja::ClassRegisterHelper<base_class_name>                 \
      sub_class_name##_register_helper(                            \
          #sub_class_name, dja::newObject<base_class_name, sub_class_name>);

/// \brief The macro to create object according to its name in string.
#define REFLECTION_CREATE_OBJECT(base_class_name, sub_class_name_as_string) \
  dja::getRegister<base_class_name>().createObject(sub_class_name_as_string)

#endif