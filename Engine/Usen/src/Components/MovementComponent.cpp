/*********************************************************************
 *   File: MovementComponent.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Actors/Actor.hpp"


DEFAULT_BODY(UMovementComponent)

void UMovementComponent::AddForwardMovement(float scaleMovement)
{
	if (!Parent)
		return;

	AActor* aParant = Cast<AActor*>(Parent);
	if (aParant)
	{
		UCollisionComponent* CollisionComponent = aParant->GetCollisionComponent();
		if (CollisionComponent)
		{
			FVector location = CollisionComponent->GetComponentLocation();
			location.x += scaleMovement * Speed;

			CollisionComponent->SetLocation(location);
		}
		else
		{

			FTransform transform = aParant->GetTransform();
			transform.Location.x += scaleMovement * Speed;

			aParant->SetTransform(transform);
		}
	}
}

void UMovementComponent::AddRightMovement(float scaleMovement)
{
	if (!Parent)
		return;

	AActor* aParant = Cast<AActor*>(Parent);
	if (aParant)
	{
		UCollisionComponent* CollisionComponent = aParant->GetCollisionComponent();
		if (CollisionComponent)
		{
			FVector location = CollisionComponent->GetComponentLocation();
			location.y += scaleMovement * Speed;

			CollisionComponent->SetLocation(location);
		}
		else
		{

			FTransform transform = aParant->GetTransform();
			transform.Location.y += scaleMovement * Speed;

			aParant->SetTransform(transform);
		}
	}
}
