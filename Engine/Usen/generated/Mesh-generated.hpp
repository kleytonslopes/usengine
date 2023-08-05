/*********************************************************************
 *   File: Mesh-generated.hpp
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
// !AMesh: ## Class Name
// !Mesh.cpp: ## File Class CPP
// !Mesh.hpp: ## File Class HPP
// !US_MESH_HPP: ## Class Definition
// !Mesh/Mesh.hpp: ## Class Head Path
// !July 2023: ## Date Creation
// !Mesh-generated.hpp: ## This file
// !hpp_AMesh_AActor: ## Class Id
// !hpp_AMesh_AActor_def: ## Class Version
// !AActor: ## Base class name
// !Actors/Actor.hpp: ## Base class path with file
//--x

#undef CURRENT_CLASS_IDENTITY_FILE
#define CURRENT_CLASS_IDENTITY_FILE hpp_AMesh_AActor

#define hpp_AMesh_AActor_def \
private: \
	using Super = AActor; using This = AMesh; \
	FString Identity{ "AMesh" }; \
    template<class T, class U> T Cast(U other) { return static_cast<T>(other); } \
public: \
	static TClassOf<AMesh> GetClass() { return TClassOf<AMesh>(); } \
private: 
	

