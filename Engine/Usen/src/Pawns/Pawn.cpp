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

APawn::APawn()
{
	This::Create();
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

APawn::~APawn()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void APawn::Create()
{
	Super::Create();

	UCameraComponent* CameraComponent = AddComponent<UCameraComponent>();
	CameraComponent->SetOwner(Owner);
	CameraComponent->SetParent(this);

	UInputComponent* InputComponent = AddComponent<UInputComponent>();
	InputComponent->SetOwner(Owner);
	InputComponent->SetParent(this);
}

void APawn::SetupInputComponent()
{

}

UInputComponent* APawn::GetInputComponent()
{
	return GetComponent<UInputComponent>();
}