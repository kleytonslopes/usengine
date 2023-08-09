/*********************************************************************
 *   File: EntitySerializer.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Serializers/EntitySerializer.hpp"
#include "Actors/Entity.hpp"
#include "Actors/Actor.hpp"
#include "Components/Component.hpp"

DEFAULT_BODY(FEntitySerializer)

void FEntitySerializer::Serialize()
{
}

void FEntitySerializer::Serialize(SeriFile& otherOut)
{
	BeginSection(otherOut, "Entity", Entity->GetId());

	SerializeComponents(otherOut);

	EndSection();
}

bool FEntitySerializer::Deserialize(const FString& scenePath)
{
	return false;
}

void FEntitySerializer::SetEntity(AEntity* entity)
{
	this->Entity = entity;
}

void FEntitySerializer::SerializeComponents(SeriFile& otherOut)
{
	AActor* actor = Cast<AActor*>(Entity);

	if (!actor)
		return;

	TMap<FString, AComponent*>::iterator it;

	Key(otherOut, "Components");
	BeginSection(otherOut);

	for (it = actor->components.begin(); it != actor->components.end(); it++)
	{
		it->second->Serialize(otherOut);
	}

	EndSection(otherOut);

}
