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

#define DECLARE_FUNCTION_PARAM(FFunctionClass, PlaceHolder, ParamList, ValueList, TemplateList) \
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
ref.Func = std::bind(function, InClass, PlaceHolder); \
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

#define DECLARE_FUNCTION_NPARAM(FFunctionClass) \
class FFunctionClass \
{ \
struct FFunctionRef { void* Ref = nullptr; std::function<void()> Func; }; \
	using Functions = TMap<FString, FFunctionRef>; \
public: \
	virtual ~FFunctionClass() { } \
	template<class ClassType, class Fx> \
	void Add(ClassType* InClass, Fx&& function) \
{ \
FFunctionRef ref{}; \
ref.Func = std::bind(function, InClass); \
ref.Ref = InClass; \
refs[InClass->GetId()] = ref; \
} \
template<class ClassType> \
void Remove(ClassType* OutClass) \
{ \
refs.erase(OutClass->GetId()); \
} \
void Broadcast() \
{ \
Functions::iterator it; \
for (it = refs.begin(); it != refs.end(); it++) \
{ \
it->second.Func(); \
} \
} \
private: Functions refs; \
};

#define PARAM_CONCAT(...) __VA_ARGS__
#define VALUE_CONCAT(...) __VA_ARGS__
#define TEMPL_CONCAT(...) __VA_ARGS__
#define PLHOL_CONCAT(...) __VA_ARGS__

#define PLACEHOLDER(A) std::placeholders::_##A
#define PLACEHOLDERS(...) PLHOL_CONCAT(__VA_ARGS__)

#define DECLARE_FUNCTION(FFunctionClass) DECLARE_FUNCTION_NPARAM(FFunctionClass)
#define DECLARE_FUNCTION_OneParam(FFunctionClass, P1, V1) DECLARE_FUNCTION_PARAM(FFunctionClass,PLACEHOLDERS(PLACEHOLDER(1)), PARAM_CONCAT(P1 V1), VALUE_CONCAT(V1), TEMPL_CONCAT(P1))
#define DECLARE_FUNCTION_TwoParam(FFunctionClass, P1, V1, P2, V2) DECLARE_FUNCTION_PARAM(FFunctionClass, PLACEHOLDERS(PLACEHOLDER(1), PLACEHOLDER(2)), PARAM_CONCAT(P1 V1, P2 V2), VALUE_CONCAT(V1, V2), TEMPL_CONCAT(P1, P2))
#define DECLARE_FUNCTION_ThreeParam(FFunctionClass, P1, V1, P2, V2, P3, V3) DECLARE_FUNCTION_PARAM(FFunctionClass, PLACEHOLDERS(PLACEHOLDER(1), PLACEHOLDER(2), PLACEHOLDER(3)), PARAM_CONCAT(P1 V1, P2 V2, P3 V3), VALUE_CONCAT(V1, V2, V3), TEMPL_CONCAT(P1, P2, P3))
#define DECLARE_FUNCTION_FourParam(FFunctionClass, P1, V1, P2, V2, P3, V3, P4, V4) DECLARE_FUNCTION_PARAM(FFunctionClass, PLACEHOLDERS(PLACEHOLDER(1), PLACEHOLDER(2), PLACEHOLDER(3), PLACEHOLDER(4)), PARAM_CONCAT(P1 V1, P2 V2, P3 V3, P4 V4), VALUE_CONCAT(V1, V2, V3, V4), TEMPL_CONCAT(P1, P2, P3, P4))

#endif // !US_FUNCTION_CLASS_HPP