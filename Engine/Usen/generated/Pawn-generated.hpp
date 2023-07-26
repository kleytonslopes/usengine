/*********************************************************************
 *   File: Pawn-generated.hpp
 *  Brief: This class is automatically generated by UsEngine ClassCreator
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#include "Core/Macros.hpp"

//--0
// !APawn: ## Class Name
// !Pawn.cpp: ## File Class CPP
// !Pawn.hpp: ## File Class HPP
// !US_PAWN_HPP: ## Class Definition
// !Pawns/Pawn.hpp: ## Class Head Path
// !July 2023: ## Date Creation
// !Pawn-generated.hpp: ## This file
// !hpp_APawn_AActor: ## Class Id
// !hpp_APawn_AActor_def: ## Class Version
// !AActor: ## Base class name
// !Actors/Actor.hpp: ## Base class path with file
//--x

#undef CURRENT_CLASS_IDENTITY_FILE
#define CURRENT_CLASS_IDENTITY_FILE hpp_APawn_AActor

#define hpp_APawn_AActor_def \
private: \
	using Super = AActor; using This = APawn; \
	FString Identity{ "APawn" }; \
    template<class T, class U> T Cast(U other) { return static_cast<T>(other); } \
private: 
	
