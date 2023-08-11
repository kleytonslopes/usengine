/*********************************************************************
 *   File: Component.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Components/Component.hpp"

DEFAULT_BODY(AComponent)

void AComponent::SetParent(AEntity* parent)
{
	this->Parent = parent;
}

void AComponent::BeginComponentSection(SeriFile& otherOut, const FString& identity)
{
	Key(otherOut, identity);
	BeginSection(otherOut);
	Key(otherOut, "id", GetId());
}
