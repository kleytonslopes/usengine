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
#include "Actors/Actor.hpp"

DEFAULT_BODY(UCollisionComponent)

void UCollisionComponent::Construct()
{
	Super::Construct();

	DefaultMass = Mass;
}

void UCollisionComponent::PostConstruct()
{
	Super::PostConstruct();

	if (!bIsDynamic)
		Mass = 0.f;

	FVector location = GetParentLocation();

	StartTransform.setIdentity();
	StartTransform.setOrigin(btVector3(location.x, location.y, location.z));
}

void UCollisionComponent::Initialize()
{
	Super::Initialize();

	if (Parent)
	{
		AActor* pActor = Cast<AActor*>(Parent);
		if (pActor && Body)
		{
			FVector pLocation = pActor->GetLocation();
			btTransform transf;
			transf.setOrigin(btVector3(pLocation.x, pLocation.y, pLocation.z));
			//Body->setWorldTransform(transf);
		}
	}
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

FVector UCollisionComponent::GetComponentLocation()
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	if (Body && bIsDynamic)
	{
		btTransform trans;

		Body->getMotionState()->getWorldTransform(trans);

		x = float(trans.getOrigin().getX());
		y = float(trans.getOrigin().getY());
		z = float(trans.getOrigin().getZ());
	}
	else
	{
		AActor* parentActor = GetParent<AActor>();
		if (parentActor)
		{
			const FVector location = parentActor->GetLocation();

			x = location.x;
			y = location.y;
			z = location.z;
		}
	}

	return FVector{ x, y, z };
}

void UCollisionComponent::SetOrigin(FVector& location)
{
	StartTransform.setOrigin(btVector3(location.x, location.y, location.z));
}