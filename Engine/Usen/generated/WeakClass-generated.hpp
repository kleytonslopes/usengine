/*********************************************************************
 *   File: WeakClass-generated.hpp
 *  Brief: This class is automatically generated by UsEngine ClassCreator
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#include "Core/Macros.hpp"
#include "Core/ClassOf.hpp"

//--0
// !IWeakClass: ## Class Name
// !WeakClass.cpp: ## File Class CPP
// !WeakClass.hpp: ## File Class HPP
// !US_WEAK_CLASS_HPP: ## Class Definition
// !Weaks/WeakClass.hpp: ## Class Head Path
// !July 2023: ## Date Creation
// !WeakClass-generated.hpp: ## This file
// !hpp_IWeakClass: ## Class Id
// !hpp_IWeakClass_def: ## Class Version
// !: ## Base class name
// !: ## Base class path with file
//--x

#undef CURRENT_CLASS_IDENTITY_FILE
#define CURRENT_CLASS_IDENTITY_FILE hpp_IWeakClass

#define hpp_IWeakClass_def \
private: \
	using This = IWeakClass; \
	FString Identity{ "IWeakClass" }; \
    template<class T, class U> T Cast(U other) { return static_cast<T>(other); } \
public: \
	static TClassOf<IWeakClass> GetClass() { return TClassOf<IWeakClass>(); } \
private: 
	

