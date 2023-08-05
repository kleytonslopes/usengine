/*********************************************************************
 *   File: Camera-generated.hpp
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
// !ACamera: ## Class Name
// !Camera.cpp: ## File Class CPP
// !Camera.hpp: ## File Class HPP
// !US_CAMERA_HPP: ## Class Definition
// !Camera/Camera.hpp: ## Class Head Path
// !July 2023: ## Date Creation
// !Camera-generated.hpp: ## This file
// !hpp_ACamera_AActor: ## Class Id
// !hpp_ACamera_AActor_def: ## Class Version
// !AActor: ## Base class name
// !Actors/Entity.hpp: ## Base class path with file
//--x

#undef CURRENT_CLASS_IDENTITY_FILE
#define CURRENT_CLASS_IDENTITY_FILE hpp_ACamera_AActor

#define hpp_ACamera_AActor_def \
private: \
	using Super = AActor; using This = ACamera; \
	FString Identity{ "ACamera" }; \
    template<class T, class U> T Cast(U other) { return static_cast<T>(other); }\
public: \
	static TClassOf<ACamera> GetClass() { return TClassOf<ACamera>(); } \
private: 
	

