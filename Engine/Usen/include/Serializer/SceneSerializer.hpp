/*********************************************************************
 *   File: SceneSerializer.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SCENE_SERIALIZER_HPP
#define	US_SCENE_SERIALIZER_HPP

#include "Core/Core.hpp"

class UScene;

class USceneSerializer
{
public:
	explicit USceneSerializer(UScene* scene);

	void Serialize();
	void Deserialize(const FString& scenePath);

private:
	UScene* Scene = nullptr;
};

#endif // !US_SCENE_SERIALIZER_HPP
