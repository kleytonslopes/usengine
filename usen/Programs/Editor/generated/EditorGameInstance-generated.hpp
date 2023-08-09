/*********************************************************************
 *   File: EditorGameInstance-generated.hpp
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
// !UEditorGameInstance: ## Class Name
// !EditorGameInstance.cpp: ## File Class CPP
// !EditorGameInstance.hpp: ## File Class HPP
// !US_EDITOR_GAME_INSTANCE_HPP: ## Class Definition
// !Framework/EditorGameInstance.hpp: ## Class Head Path
// !August 2023: ## Date Creation
// !EditorGameInstance-generated.hpp: ## This file
// !hpp_UEditorGameInstance_UGameInstance: ## Class Id
// !hpp_UEditorGameInstance_UGameInstance_def: ## Class Version
// !UGameInstance: ## Base class name
// !Framework/GameInstance.hpp: ## Base class path with file
//--x

#undef CURRENT_CLASS_IDENTITY_FILE
#define CURRENT_CLASS_IDENTITY_FILE hpp_UEditorGameInstance_UGameInstance

#define hpp_UEditorGameInstance_UGameInstance_def \
private: \
	using Super = UGameInstance; using This = UEditorGameInstance; \
	FString Identity{ "UEditorGameInstance" }; \
    template<class T, class U> T Cast(U other) { return static_cast<T>(other); } \
public: \
	static TClassOf<UEditorGameInstance> GetClass() { return TClassOf<UEditorGameInstance>(); } \
private: 
	

