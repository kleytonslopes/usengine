/*********************************************************************
 *   File: ComponentSerializer.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Serializer/ComponentSerializer.hpp"
#include "Components/Interface/IComponent.hpp"

UComponentSerializer::UComponentSerializer(IComponent* component)
	: Component{ component }
{
}

UComponentSerializer::~UComponentSerializer()
{

}

void UComponentSerializer::Serialize()
{
}

void UComponentSerializer::Serialize(YAML::Emitter& otherOut)
{

}

bool UComponentSerializer::Deserialize(const FString& scenePath)
{
	return false;
}
