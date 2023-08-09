/*********************************************************************
 *   File: GameInstance-generated.hpp
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
// !UGameInstance: ## Class Name
// !GameInstance.cpp: ## File Class CPP
// !GameInstance.hpp: ## File Class HPP
// !US_GAME_INSTANCE_HPP: ## Class Definition
// !Framework/GameInstance.hpp: ## Class Head Path
// !July 2023: ## Date Creation
// !GameInstance-generated.hpp: ## This file
// !hpp_UGameInstance_BClass: ## Class Id
// !hpp_UGameInstance_BClass_def: ## Class Version
// !BClass: ## Base class name
// !Base/Class.hpp: ## Base class path with file
//--x

#undef CURRENT_CLASS_IDENTITY_FILE
#define CURRENT_CLASS_IDENTITY_FILE hpp_UGameInstance_BClass

#define hpp_UGameInstance_BClass_def \
private: \
	using Super = BClass; using This = UGameInstance; \
	FString Identity{ "UGameInstance" }; \
    template<class T, class U> T Cast(U other) { return static_cast<T>(other); } \
public: \
	static TClassOf<UGameInstance> GetClass() { return TClassOf<UGameInstance>(); } \
    FString GetIdentity() { return Identity; } \
private: 
	

