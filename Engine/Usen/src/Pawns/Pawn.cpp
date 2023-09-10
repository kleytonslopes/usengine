/*********************************************************************
 *   File: Pawn.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Pawns/Pawn.hpp"
#include "Components/CameraComponent.hpp"
#include "Components/InputComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Components/CapsuleComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Runtime/Application.hpp"
#include "Core/Attachment.hpp"

DEFAULT_BODY(APawn)

void APawn::Construct()
{
	Super::Construct();

	bCanUpdate = true;

	CameraComponent = AddComponent<UCameraComponent>();
	InputComponent = AddComponent<UInputComponent>();
	CapsuleComponent = AddComponent<UCapsuleComponent>();
	MovementComponent = AddComponent<UMovementComponent>();

	CollisionComponent = CapsuleComponent;
}

void APawn::PostConstruct()
{
	Super::PostConstruct();
}

void APawn::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (CollisionComponent)
	{
		FVector location = CollisionComponent->GetWorldPosition();
		TransformComponent->SetLocation(location);
		OnLocationChangedEvent.Broadcast(location);
	}
	if (Attachments)
	{
		Attachments->UpdateLocation();
	}
}

UInputComponent* APawn::GetInputComponent()
{
	return GetComponent<UInputComponent>();
}

UCapsuleComponent* APawn::GetCapsuleComponent()
{
	return GetComponent<UCapsuleComponent>();
}

void APawn::MoveForward(float scale)
{
	const float deltaTime = GetApplication()->GetDeltaTime();
	float movementScale = scale * deltaTime;

	MovementComponent->AddForwardMovement(movementScale);
}

void APawn::MoveRight(float scale)
{
	const float deltaTime = GetApplication()->GetDeltaTime();
	float movementScale = scale * deltaTime;

	MovementComponent->AddRightMovement(movementScale);
}

void APawn::Jump()
{
	const float jumpZ = MovementComponent->JumpScale;
	CapsuleComponent->HandleJump(jumpZ);
}

FVector APawn::GetCapsuleLocation()
{
	if (CollisionComponent)
	{
		return CollisionComponent->GetWorldPosition();
	}

	return FVector{ 0.f };
}

void APawn::SetMesh(AMesh* mesh)
{
	Mesh = mesh;
}

AMesh* APawn::GetMesh()
{
	return Mesh;
}

