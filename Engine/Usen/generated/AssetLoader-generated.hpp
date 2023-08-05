/*********************************************************************
 *   File: AssetLoader-generated.hpp
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
// !UAssetLoader: ## Class Name
// !AssetLoader.cpp: ## File Class CPP
// !AssetLoader.hpp: ## File Class HPP
// !US_ASSET_LOADER_HPP: ## Class Definition
// !Utils/AssetLoader.hpp: ## Class Head Path
// !July 2023: ## Date Creation
// !AssetLoader-generated.hpp: ## This file
// !hpp_UAssetLoader_IWeakClass: ## Class Id
// !hpp_UAssetLoader_IWeakClass_def: ## Class Version
// !IWeakClass: ## Base class name
// !Weaks/WeakClass.hpp: ## Base class path with file
//--x

#undef CURRENT_CLASS_IDENTITY_FILE
#define CURRENT_CLASS_IDENTITY_FILE hpp_UAssetLoader_IWeakClass

#define hpp_UAssetLoader_IWeakClass_def \
private: \
	using Super = IWeakClass; using This = UAssetLoader; \
	FString Identity{ "UAssetLoader" }; \
    template<class T, class U> T Cast(U other) { return static_cast<T>(other); } \
public: \
	static TClassOf<UAssetLoader> GetClass() { return TClassOf<UAssetLoader>(); } \
private: 
	

