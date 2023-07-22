/*********************************************************************
 *   File: EntitySerializer.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Serializer/EntitySerializer.hpp"
#include "Framework/Entity.hpp"

UEntitySerializer::UEntitySerializer(UEntity* entity) 
	: Entity{ entity }
{
}

UEntitySerializer::~UEntitySerializer()
{

}

void UEntitySerializer::Serialize()
{

}

void UEntitySerializer::Serialize(YAML::Emitter& otherOut)
{
	BeginMap(otherOut, "Entity", Entity->Id);

	SerializeComponents(otherOut);

	EndMap(otherOut);
}

bool UEntitySerializer::Deserialize(const FString& scenePath)
{
	return false;
}

void UEntitySerializer::SerializeComponents(YAML::Emitter& otherOut)
{
	TMap<FString, IComponent*>::iterator it;

	Key(otherOut, "Components");
	BeginMap(otherOut);
	for (it = Entity->components.begin(); it != Entity->components.end(); it++)
	{
		it->second->Serialize(otherOut);
	}
	EndMap(otherOut);

}
