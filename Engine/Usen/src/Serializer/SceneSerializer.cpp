/*********************************************************************
 *   File: SceneSerializer.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Serializer/SceneSerializer.hpp"
#include "Framework/Scene.hpp"

USceneSerializer::USceneSerializer(UScene* scene)
	: Scene{ scene }
{
}

void USceneSerializer::Serialize()
{

}

void USceneSerializer::Deserialize(const FString& scenePath)
{
}
