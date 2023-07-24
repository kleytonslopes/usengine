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

FEntitySerializer::FEntitySerializer()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

FEntitySerializer::~FEntitySerializer()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void FEntitySerializer::Serialize()
{
}

void FEntitySerializer::Serialize(SeriFile& otherOut)
{
}

bool FEntitySerializer::Deserialize(const FString& scenePath)
{
	return false;
}

void FEntitySerializer::SetEntity(AEntity* entity)
{
	this->Entity = entity;
}

void FEntitySerializer::SerializeComponents()
{
	AActor* actor = Cast<AActor*>(Entity);
}
