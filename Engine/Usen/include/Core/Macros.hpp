/*********************************************************************
 *   File: Macros.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_MACROS_HPP
#define	US_MACROS_HPP

#include "Core/Core.hpp"

#define STRINGFY_INNER(A) #A
#define STRINGFY_ARGS(A) STRINGFY_INNER(A)
#define STRINGFY(...) STRINGFY_ARGS(__VA_ARGS__)

#define DEFAULT_BODY_GENERATED_FILTER_IN(A,B,C) A##B##C
#define DEFAULT_BODY_GENERATED_FILTER(A,B,C) DEFAULT_BODY_GENERATED_FILTER_IN(A,B,C)
#define DEFAULT_BODY_GENERATED(...) DEFAULT_BODY_GENERATED_FILTER(CURRENT_CLASS_IDENTITY_FILE,_,def);

#define UASSERT(COND, MSG) \
ULOG(ELogLevel::ELL_FATAL, MSG); \
assert(COND && MSG)

#define DEFINE_DEFAULT_CONSTTRUCTORS_DESTRUCTORS(ClassName) \
explicit ClassName(); \
virtual ~ClassName(); \

#define DEFAULT_BODY(ClassName) \
ClassName::ClassName() { Identity = STRINGFY(ClassName); } \
ClassName::~ClassName() { } \

#define N_ENABLE_DEFINE_OPERATOR_CPY
#  if defined(ENABLE_DEFINE_OPERATOR_CPY)
#    define DEFINE_OPERATOR_CPY(ClassName)  \
       ClassName(const ClassName& other) = default; \
       ClassName& operator=(const ClassName& other) = default;
#  else
#    define DEFINE_OPERATOR_CPY(ClassName)
#endif // ENABLE_DEFINE_OPERATOR_CPY

#define N_ENABLE_DEFINE_OPERATOR_MOV
#  if defined(ENABLE_DEFINE_OPERATOR_MOV)
#    define DEFINE_OPERATOR_MOV(ClassName) \
       ClassName(ClassName&& other) = default; \
       ClassName& operator=(ClassName&& other) = default;
#  else
#    define DEFINE_OPERATOR_MOV(ClassName)
#endif // ENABLE_DEFINE_OPERATOR_MOV

#define DEFINE_CAST_FUNCTION() \
template<class T, class U> T Cast(U other) { return static_cast<T>(other); }\

#define DEFINE_IDENTITY_BODY() \
FString GetIdentity() { return Identity; } \

#define DEFINE_GET_CLASS(ClassName) \
static TClassOf<ClassName> GetClass() { return TClassOf<ClassName>(); } \

#endif // !US_MACROS_HPP