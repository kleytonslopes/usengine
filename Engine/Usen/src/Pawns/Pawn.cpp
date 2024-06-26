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

DEFAULT_BODY(APawn)

void APawn::Construct()
{
	UCameraComponent* CameraComponent = AddComponent<UCameraComponent>();
	CameraComponent->SetOwner(Owner);
	CameraComponent->SetParent(this);

	UInputComponent* InputComponent = AddComponent<UInputComponent>();
	InputComponent->SetOwner(Owner);
	InputComponent->SetParent(this);

	UCapsuleComponent* CapsuleComponent = AddComponent<UCapsuleComponent>();
	CapsuleComponent->SetOwner(Owner);
	CapsuleComponent->SetParent(this);

	Super::Construct();
}

void APawn::PostConstruct()
{
	Super::PostConstruct();
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
	FTransform transform = GetTransform();

	transform.Location.x += scale;

	SetTransform(transform);
}

void APawn::MoveRight(float scale)
{
	FTransform transform = GetTransform();

	transform.Location.y += scale;

	SetTransform(transform);
}
