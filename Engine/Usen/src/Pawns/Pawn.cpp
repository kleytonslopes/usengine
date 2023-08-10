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

DEFAULT_BODY(APawn)

void APawn::Create()
{
	UCameraComponent* CameraComponent = AddComponent<UCameraComponent>();
	CameraComponent->SetOwner(Owner);
	CameraComponent->SetParent(this);

	UInputComponent* InputComponent = AddComponent<UInputComponent>();
	InputComponent->SetOwner(Owner);
	InputComponent->SetParent(this);

	Super::Create();
}

void APawn::PostCreate()
{
	GetInputComponent()->Create();

	Super::PostCreate();
}

UInputComponent* APawn::GetInputComponent()
{
	return GetComponent<UInputComponent>();
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
