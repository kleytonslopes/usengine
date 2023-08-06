/*********************************************************************
 *   File: CollisionComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Components/CollisionComponent.hpp"

UCollisionComponent::UCollisionComponent()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UCollisionComponent::~UCollisionComponent()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UCollisionComponent::Create()
{
	StartTransform.setIdentity();
	StartTransform.setOrigin(btVector3(0.f, 0.f, 0.f));

	DefaultMass = Mass;

	if (!bIsDynamic)
		Mass = 0.f;

	Super::Create();
}

void UCollisionComponent::SetIsDynamic(const bool& isDynamic)
{
	if (isDynamic)
	{
		bIsDynamic = true;
		Mass = DefaultMass;
	}
	else
	{
		bIsDynamic = false;
		Mass = 0.f;
	}
}

FVector UCollisionComponent::GetLocationCalculated(const btVector3& btLocation)
{
	float x = btLocation[0];
	float y = btLocation[1];
	float z = btLocation[2];

	if (Body)
	{
		btTransform trans;
		if (Body && Body->getMotionState())
		{
			Body->getMotionState()->getWorldTransform(trans);

			x = float(trans.getOrigin().getX());
			y = float(trans.getOrigin().getY());
			z = float(trans.getOrigin().getZ());
		}
		else
		{
			FLogger::Warning("Woops");
		}
	}

	return FVector{ x, y, z };
}
