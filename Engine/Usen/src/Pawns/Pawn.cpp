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
#include "Runtime/Application.hpp"

DEFAULT_BODY(APawn)

void APawn::Construct()
{
	Super::Construct();

	UCameraComponent* CameraComponent = AddComponent<UCameraComponent>();
	UInputComponent* InputComponent = AddComponent<UInputComponent>();
	//UCapsuleComponent* CapsuleComponent = AddComponent<UCapsuleComponent>();
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
	const float deltaTime = GetApplication()->GetDeltaTime();
	transform.Location.x += scale * deltaTime * Speed;

	SetTransform(transform);
}

void APawn::MoveRight(float scale)
{
	FTransform transform = GetTransform();
	const float deltaTime = GetApplication()->GetDeltaTime();
	transform.Location.y += scale * deltaTime * Speed;

	SetTransform(transform);
}
