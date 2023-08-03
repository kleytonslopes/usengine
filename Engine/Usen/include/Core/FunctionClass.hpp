/*********************************************************************
 *   File: FunctionClass.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef US_FUNCTION_CLASS_HPP
#define	US_FUNCTION_CLASS_HPP

#include "Core/MinimalCore.hpp"
#include <functional>

#define DECLARE_FUNCTION_PARAM(FFunctionClass, ParamList, ValueList, TemplateList) \
class FFunctionClass \
{ \
struct FFunctionRef { void* Ref = nullptr; std::function<void(TemplateList)> Func; }; \
	using Functions = TMap<FString, FFunctionRef>; \
public: \
	virtual ~FFunctionClass() { } \
	template<class ClassType, class Fx> \
	void Add(ClassType* InClass, Fx&& function) \
{ \
FFunctionRef ref{}; \
ref.Func = std::bind(function, InClass, std::placeholders::_1); \
ref.Ref = InClass; \
refs[InClass->GetId()] = ref; \
} \
template<class ClassType> \
void Remove(ClassType* OutClass) \
{ \
refs.erase(OutClass->GetId()); \
} \
void Broadcast(ParamList) \
{ \
Functions::iterator it; \
for (it = refs.begin(); it != refs.end(); it++) \
{ \
it->second.Func(ValueList); \
} \
} \
private: Functions refs; \
};

#define PARAM_CONCAT(...) __VA_ARGS__
#define VALUE_CONCAT(...) __VA_ARGS__
#define TEMPL_CONCAT(...) __VA_ARGS__

#define DECLARE_FUNCTION(FFunctionClass) DECLARE_FUNCTION_PARAM(FFunctionClass, PARAM_CONCAT(), VALUE_CONCAT(), TEMPL_CONCAT())
#define DECLARE_FUNCTION_OneParam(FFunctionClass, P1, V1) DECLARE_FUNCTION_PARAM(FFunctionClass, PARAM_CONCAT(P1 V1), VALUE_CONCAT(V1), TEMPL_CONCAT(P1))

#endif // !US_FUNCTION_CLASS_HPP