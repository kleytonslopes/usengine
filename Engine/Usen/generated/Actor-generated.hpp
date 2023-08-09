/*********************************************************************
 *   File: Actor-generated.hpp
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
// !AActor: ## Class Name
// !Actor.cpp: ## File Class CPP
// !Actor.hpp: ## File Class HPP
// !US_ACTOR_HPP: ## Class Definition
// !Actors/Actor.hpp: ## Class Head Path
// !July 2023: ## Date Creation
// !Actor-generated.hpp: ## This file
// !hpp_AActor_AEntity: ## Class Id
// !hpp_AActor_AEntity_def: ## Class Version
// !AEntity: ## Base class name
// !Actors/Entity.hpp: ## Base class path with file
//--x

#undef CURRENT_CLASS_IDENTITY_FILE
#define CURRENT_CLASS_IDENTITY_FILE hpp_AActor_AEntity

#define hpp_AActor_AEntity_def \
private: \
	using Super = AEntity; using This = AActor; \
    DEFINE_CAST_FUNCTION() \
public: \
    DEFINE_DEFAULT_CONSTTRUCTORS_DESTRUCTORS(AActor) \
	DEFINE_OPERATOR_CPY(AActor) \
	DEFINE_OPERATOR_MOV(AActor) \
	DEFINE_IDENTITY_BODY() \
	DEFINE_GET_CLASS(AActor) \
private: 
	

