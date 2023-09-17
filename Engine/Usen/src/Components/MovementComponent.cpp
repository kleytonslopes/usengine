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
#include "Physics/PhysicsSystemPhysX.hpp"
#include "Framework/Scene.hpp"
#include "Camera/Camera.hpp"

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
			FVector forwardVector = GetScene()->GetCamera()->GetForwardVector();
			forwardVector.y = 0.f;
			CollisionComponent->AddMovement(scaleMovement, Speed, -forwardVector);
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
			FVector forwardVector = GetScene()->GetCamera()->GetRightVector();
			forwardVector.y = 0.f;
			CollisionComponent->AddMovement(scaleMovement, Speed, -forwardVector);
			FVector newLocation = CollisionComponent->GetWorldPosition();
			aParant->SetLocation(newLocation);

			////FVector location = GetScene()->GetCamera()->GetLocation();
			////FVector fwd = GetScene()->GetCamera()->GetForwardVector();
			////FVector up = GetScene()->GetCamera()->GetUpVector();
			////
			////location -= glm::normalize(glm::cross(fwd, up));// *scaleMovement * 0.0001f;
			////CollisionComponent->AddMovement(location);
			///*
			//*/
			//FVector rightVector = GetScene()->GetCamera()->GetRightVector();
			//rightVector = glm::normalize(rightVector);
			//location.y = 0.f;
			//CollisionComponent->AddMovement(-scaleMovement, Speed, location);
			////FVector newLocation = CollisionComponent->GetWorldPosition();
			////aParant->SetLocation(newLocation);
		}
		else
		{
			AFTransform transform = aParant->GetTransform();
			transform.GetLocation().z += -scaleMovement * Speed;
			aParant->SetTransform(transform);
		}
	}
}

void UMovementComponent::StartJump()
{
	APawn* aParant = Cast<APawn*>(Parent);
	if (aParant)
	{
		UCapsuleComponent* CollisionComponent = aParant->GetCapsuleComponent();
		if (CollisionComponent && CollisionComponent->CanHandleJump())
		{
			FVector currentLocation = CollisionComponent->GetWorldPosition();
			FVector targetLocation = currentLocation;
			targetLocation.y += JumpScale;
			CollisionComponent->HandleJump(currentLocation, targetLocation);
		}
	}
}

void UMovementComponent::EndJump()
{
	APawn* aParant = Cast<APawn*>(Parent);
	if (aParant)
	{
		UCapsuleComponent* CollisionComponent = aParant->GetCapsuleComponent();
		if (CollisionComponent && CollisionComponent->IsJumping())
		{
			CollisionComponent->StopJump();
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
			if (CollisionComponent && !CollisionComponent->IsJumping())
			{
				CollisionComponent->AddMovement(deltaTime, GetPhysicsSystemPhysX()->GravityScale* 2, EAxis::Y);
				FVector newLocation = CollisionComponent->GetWorldPosition();
				aParant->SetLocation(newLocation);
			}
			else if (CollisionComponent && CollisionComponent->IsJumping())
			{
				const FVector currentLocation = CollisionComponent->GetWorldPosition();
				FVector nextLocation = currentLocation;
				nextLocation.y += JumpScale * deltaTime * 0.0001f;
				bool reached;

				CollisionComponent->CalculeJump(nextLocation, reached);

				if (!reached)
				{
					CollisionComponent->AddMovement(deltaTime, -GetPhysicsSystemPhysX()->GravityScale * JumpScale, EAxis::Y);
					FVector newLocation = CollisionComponent->GetWorldPosition();
					aParant->SetLocation(newLocation);
				}
				else
				{
					CollisionComponent->StopJump();
				}
			}
		}
	}
}
