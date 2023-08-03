/*********************************************************************
 *   File: AssetLoader.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_ASSET_LOADER_HPP
#define	US_ASSET_LOADER_HPP


#include "Weaks/WeakClass.hpp"
#include "AssetLoader-generated.hpp"

class UAssetLoader : public IWeakClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UAssetLoader();
	virtual ~UAssetLoader();

	void LoadModel(static FString& modelPath);
};

#endif // !US_ASSET_LOADER_HPP