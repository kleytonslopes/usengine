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
#include "Actors/Actor.hpp"

DEFAULT_BODY(AComponent)

void AComponent::SetParent(AEntity* parent)
{
	this->Parent = parent;
}

FVector AComponent::GetParentLocation()
{
	if (Parent)
	{
		AActor* aParent = Cast<AActor*>(Parent);
		if (aParent)
		{
			return aParent->GetLocation();
		}
	}
	return FVector{0};
}

FTransform AComponent::GetParentTransform()
{
	if (Parent)
	{
		AActor* aParent = Cast<AActor*>(Parent);
		if (aParent)
		{
			return aParent->GetTransform();
		}
	}
	return FTransform{};
}

void AComponent::BeginComponentSection(SeriFile& otherOut, const FString& identity)
{
	Key(otherOut, identity);
	BeginSection(otherOut);
	Key(otherOut, "id", GetId());
}
