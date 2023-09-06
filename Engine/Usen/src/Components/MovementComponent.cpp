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
#include "Components/CapsuleComponent.hpp"
#include "Actors/Actor.hpp"
#include "Pawns/Pawn.hpp"

DEFAULT_BODY(UMovementComponent)

void UMovementComponent::Construct()
{
	Super::Construct();

	bCanUpdate = true;
}

void UMovementComponent::AddForwardMovement(float scaleMovement)
{
	if (!Parent)
		return;

	APawn* aParant = Cast<APawn*>(Parent);
	if (aParant)
	{
		UCapsuleComponent* CollisionComponent = aParant->GetCapsuleComponent();
		if (CollisionComponent)
		{
			CollisionComponent->AddMovement(-scaleMovement, Speed, EAxis::X);
			FVector newLocation = CollisionComponent->GetWorldPosition();
			aParant->SetLocation(newLocation);
		}
		else
		{
			AFTransform transform = aParant->GetTransform();
			transform.GetLocation().x += -scaleMovement * Speed;
			aParant->SetTransform(transform);
		}
	}
}

void UMovementComponent::AddRightMovement(float scaleMovement)
{
	if (!Parent)
		return;

	APawn* aParant = Cast<APawn*>(Parent);
	if (aParant)
	{
		UCapsuleComponent* CollisionComponent = aParant->GetCapsuleComponent();
		if (CollisionComponent)
		{
			CollisionComponent->AddMovement(-scaleMovement, Speed, EAxis::Z);
			FVector newLocation = CollisionComponent->GetWorldPosition();
			aParant->SetLocation(newLocation);
		}
		else
		{
			AFTransform transform = aParant->GetTransform();
			transform.GetLocation().z += -scaleMovement * Speed;
			aParant->SetTransform(transform);
		}
	}
}

void UMovementComponent::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (bUseGravity)
	{
		APawn* aParant = Cast<APawn*>(Parent);
		if (aParant)
		{
			UCapsuleComponent* CollisionComponent = aParant->GetCapsuleComponent();
			if (CollisionComponent)
			{
				CollisionComponent->AddMovement(deltaTime, -10.f, EAxis::Y);
				FVector newLocation = CollisionComponent->GetWorldPosition();
				aParant->SetLocation(newLocation);
			}
		}
	}
}
