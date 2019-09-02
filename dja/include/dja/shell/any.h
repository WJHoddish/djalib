#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// This is a cpp implementation meta class using RTTI for type erase.
//

#ifndef DJA_ANY_H_
#define DJA_ANY_H_

#include <memory>
#include <typeindex>
#include <iostream>

namespace dja {
class Any {
 public:
  /// \brief The constructor.
  Any() : type_(std::type_index(typeid(void))) {}

  /// \brief The copy constructor.
  Any(const Any& src) : ptr_(src.clone()), type_(src.type_) {}

  /// \brief The move constructor.
  Any(Any&& src) noexcept : ptr_(std::move(src.ptr_)), type_(src.type_) {}

  /// \brief To get the origin type.
  /// \attention It uses std::decay to remove reference.
  template <
      typename U,
      class = typename std::enable_if<
          !std::is_same<typename std::decay<U>::type, Any>::value, U>::type>
  Any(U&& value)
      : ptr_(new Derived<typename std::decay<U>::type>(std::forward<U>(value))),
        type_(std::type_index(typeid(typename std::decay<U>::type))) {}

  /// \brief Judge if the object is empty.
  bool isNull() const { return !bool(ptr_); }

  /// \brief Make a judgment about its type.
  /// \attention It uses the cpp RTTI.
  template <class U>
  bool is() const {
    return (type_ == std::type_index(typeid(U)));
  }

  /// \brief Cast the Any object to its real type.
  template <class U>
  U& any_cast() {
    if (!is<U>()) {
      std::cout << "cannot cast " << typeid(U).name() << " to " << type_.name()
                << "\n";
      throw std::bad_cast();
    }
    auto derived = dynamic_cast<Derived<U>*>(ptr_.get());
    return derived->data_;
  }

  /// \brief Operator overload for value assignment.
  Any& operator=(const Any& src) {
    if (ptr_ != src.ptr_) {
      ptr_ = src.clone();
      type_ = src.type_;
    }
    return *this;
  }

  Any& operator=(Any&& src) noexcept {
    if (ptr_ != src.ptr_) {
      ptr_ = std::move(src.ptr_);
      type_ = src.type_;
    }
    return *this;
  }

 private:
  /// \brief An abstract class lives in Any.
  struct Base {
    /// \brief The destructor, to make derived objects can be deleted rightly.
    virtual ~Base() {}

    /// \brief A pure virtual function.
    virtual std::unique_ptr<Base> clone() const = 0;
  };

  /// \brief A derived class lives in Any.
  template <typename T>
  struct Derived : Base {
    /// \brief The constructor.
    template <typename U>
    Derived(U&& value) : data_(std::forward<U>(value)) {}

    /// \brief Return a new smart point which handles a heap memory.
    std::unique_ptr<Base> clone() const {
      return std::unique_ptr<Base>(new Derived<T>(data_));
    }

    T data_;  ///< \brief the template data
  };

  std::unique_ptr<Base> clone() const {
    if (ptr_ != nullptr) {
      return ptr_->clone();
    } else {
      return nullptr;
    }
  }

  ///< the type info
  std::type_index type_;
  ///< the pointer to your data
  std::unique_ptr<Base> ptr_;
};
}  // namespace dja

#endif
