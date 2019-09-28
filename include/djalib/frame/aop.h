#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang <wjhgeneral@outlook.com>
// Aspect Oriented Programming frame work.
//

#ifndef DJA_AOP_H_
#define DJA_AOP_H_

#include "shell/any_map.h"

namespace dja {
class AspectVars {
 public:
  AspectVars(AnyMap& vars) : vars_(vars) {}

  virtual ~AspectVars() {}

  void id() const { std::cout << &vars_ << "\n"; }

 protected:
  AnyMap& vars_;
};

class FuncPre {
 public:
  virtual void pre() = 0;
};

class FuncAft {
 public:
  virtual void aft() = 0;
};

class AspectPre : public AspectVars, public FuncPre {
 public:
  AspectPre(AnyMap& vars) : AspectVars(vars) {}

  virtual ~AspectPre() {}
};

class AspectAft : public AspectVars, public FuncAft {
 public:
  AspectAft(AnyMap& vars) : AspectVars(vars) {}

  virtual ~AspectAft() {}
};

class AspectFull : public AspectVars, public FuncPre, public FuncAft {
 public:
  AspectFull(AnyMap& vars) : AspectVars(vars) {}

  virtual ~AspectFull() {}
};

template <typename F>
class Aop : public NonCopyable {
 public:
  Aop(F&& func) : func_(std::forward<F>(func)) {}

  /// \brief Load each aspect by recursion.
  template <typename Head, typename... Tail>
  auto invoke(AnyMap& args, Head&& headAspect, Tail&&... tailAspect) ->
      typename std::enable_if<std::is_base_of<FuncPre, Head>::value &&
                              std::is_base_of<FuncAft, Head>::value &&
                              std::is_base_of<AspectVars, Head>::value>::type {
    headAspect.pre();
    invoke(args, std::forward<Tail>(tailAspect)...);
    headAspect.aft();
  }

  template <typename Head, typename... Tail>
  auto invoke(AnyMap& args, Head&& headAspect, Tail&&... tailAspect) ->
      typename std::enable_if<std::is_base_of<FuncPre, Head>::value &&
                              !std::is_base_of<FuncAft, Head>::value &&
                              std::is_base_of<AspectVars, Head>::value>::type {
    headAspect.pre();
    invoke(args, std::forward<Tail>(tailAspect)...);
  }

  template <typename Head, typename... Tail>
  auto invoke(AnyMap& args, Head&& headAspect, Tail&&... tailAspect) ->
      typename std::enable_if<!std::is_base_of<FuncPre, Head>::value &&
                              std::is_base_of<FuncAft, Head>::value &&
                              std::is_base_of<AspectVars, Head>::value>::type {
    invoke(args, std::forward<Tail>(tailAspect)...);
    headAspect.aft();
  }

  /// \brief The recursive endpoint.
  template <typename T>
  auto invoke(AnyMap& args, T&& aspect) ->
      typename std::enable_if<std::is_base_of<FuncPre, T>::value &&
                              std::is_base_of<FuncAft, T>::value &&
                              std::is_base_of<AspectVars, T>::value>::type {
    aspect.pre();
    func_(args);
    aspect.aft();
  }

  template <typename T>
  auto invoke(AnyMap& args, T&& aspect) ->
      typename std::enable_if<std::is_base_of<FuncPre, T>::value &&
                              !std::is_base_of<FuncAft, T>::value &&
                              std::is_base_of<AspectVars, T>::value>::type {
    aspect.pre();
    func_(args);
  }

  template <typename T>
  auto invoke(AnyMap& args, T&& aspect) ->
      typename std::enable_if<!std::is_base_of<FuncPre, T>::value &&
                              std::is_base_of<FuncAft, T>::value &&
                              std::is_base_of<AspectVars, T>::value>::type {
    func_(args);
    aspect.aft();
  }

 private:
  F func_;
};

template <typename... Asps, typename F>
void invoke(F&& f, AnyMap& args) {
  Aop<F> aop_frame(std::forward<F>(f));
  aop_frame.invoke(args, Asps(args)...);
}
}  // namespace dja
#endif
