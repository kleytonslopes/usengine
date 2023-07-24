/*********************************************************************
 *   File: Entity.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Actors/Entity.hpp"
#include "Core/Guid.hpp"

AEntity::AEntity()
{
	Id = FGuid::NewGuid();
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created with id %s!", Identity.c_str(), Id.c_str()));
}

AEntity::~AEntity()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Created!", Identity.c_str()));
}

void AEntity::SetOwner(AEntity* owner)
{
	this->Owner = owner;
}

void AEntity::Draw(float deltaTime)
{
}
