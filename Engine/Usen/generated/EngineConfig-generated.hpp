/*********************************************************************
 *   File: EngineConfig-generated.hpp
 *  Brief: This class is automatically generated by UsEngine ClassCreator
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#include "Core/Macros.hpp"
#include "Core/ClassOf.hpp"

//--0
// !FEngineConfig: ## Class Name
// !EngineConfig.cpp: ## File Class CPP
// !EngineConfig.hpp: ## File Class HPP
// !US_ENGINE_CONFIG_HPP: ## Class Definition
// !Configs/EngineConfig.hpp: ## Class Head Path
// !August 2023: ## Date Creation
// !EngineConfig-generated.hpp: ## This file
// !hpp_FEngineConfig: ## Class Id
// !hpp_FEngineConfig_def: ## Class Version
// !: ## Base class name
// !: ## Base class path with file
//--x

#undef CURRENT_CLASS_IDENTITY_FILE
#define CURRENT_CLASS_IDENTITY_FILE hpp_FEngineConfig

#define hpp_FEngineConfig_def \
private: \
	using This = FEngineConfig; \
	FString Identity{ "FEngineConfig" }; \
    template<class T, class U> T Cast(U other) { return static_cast<T>(other); } \
public: \
	static TClassOf<FEngineConfig> GetClass() { return TClassOf<FEngineConfig>(); } \
    FString GetIdentity() { return Identity; } \
private: 
	

