#pragma once
// for example: use a class name (a string) to construct a object.
#ifndef _REFLECTION_H_
#define _REFLECTION_H_

#include <map>
#include <string>
#include <cassert>
#include <iostream>

namespace djalib
{
	template<typename T>
	class ClassRegister
	{
	public:
		typedef T ClassName;
		typedef ClassName* (*ClassConstructor)(void);				// function pointer: 'Constructor'.
																	// map type: 
																	// 1. class name. 
		typedef std::map<std::string, ClassConstructor> ClassMap;	// 2. function pointer to its constructor.

	private:
		ClassMap mapping;
	
	public:
		void AddConstructor(
			const std::string name,
			ClassConstructor constructor) {
			// insert a new constructor into the map.
			typename ClassMap::iterator it = mapping.find(name);
			assert(it == mapping.end());
			mapping[name] = constructor;
		}
		
		ClassName* CreateObject(
			const std::string class_name) const {
			// create an object according to the class name (a string).
			typename ClassMap::const_iterator it = mapping.find(class_name);
			if (it == mapping.end()) {
				return
					nullptr;
			}
			else {
				return
					(*(it->second))();
			}
		}

	public:
		void display() {
			std::cout
				<< "map size: " << mapping.size() << "\n";
		}
	};
	
	// use a fuction to store static object(s).
	// * a great use of template function!!!
	template <typename BaseClassName>
	ClassRegister<BaseClassName>& GetRegister() {
		static ClassRegister<BaseClassName> 
			class_register;
		return 
			class_register;
	}

	// the constructor of each class.
	// * the mapping will store the pointer towards this function!
	template <typename BaseClassName, typename SubClassName>
	BaseClassName* NewObject() {
		return 
			new SubClassName();
	}

	// offer a "helper" for each reflection class. do registration when constructing.
	template<typename BaseClassName>
	class ClassRegisterHelper
	{
	public:
		ClassRegisterHelper(
			const std::string sub_class_name,
			typename ClassRegister<BaseClassName>::ClassConstructor constructor) {
			// the register procedure.
			GetRegister<BaseClassName>().AddConstructor(sub_class_name, constructor);
			GetRegister<BaseClassName>().display();
		}
		~ClassRegisterHelper() {}
	};

	// marco.1: register "class name" & "function pointer to its constructor".
	// * you need to provide "base class name" & "inherited class name"!
#define REFLECTION_REGISTER(base_class_name, sub_class_name) \
	static djalib::ClassRegisterHelper<base_class_name> \
		sub_class_name##_register_helper( \
			#sub_class_name, \
			djalib::NewObject<base_class_name, sub_class_name>);

	// marco.2: create object.
#define REFLECTION_CREATOR(base_class_name, sub_class_name_as_string) \
	djalib::GetRegister<base_class_name>().CreateObject(sub_class_name_as_string)
	
	// don't let any " " (blank) exists behind '\' sign within the macro definition!

}

#endif
