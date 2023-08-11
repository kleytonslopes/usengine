/*********************************************************************
 *   File: PlayerController.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Controllers/PlayerController.hpp"
#include "Input/InputManagement.hpp"
#include "Pawns/Pawn.hpp"

DEFAULT_BODY(UPlayerController)

void UPlayerController::Initialize()
{
	Super::Initialize();

	SetupInputComponent();
}

void UPlayerController::SetupInputComponent()
{
	UInputManagement* InputManagement = GetInputManagement();

	InputManagement->AddAction("Exit", this, EKeyHandler::KEY_PRESSED, &This::ExitAction);
	InputManagement->AddAction("MoveForward", this, EKeyHandler::KEY_PRESSED, &This::MoveForward);
	InputManagement->AddAction("MoveBackward", this, EKeyHandler::KEY_PRESSED, &This::MoveBackward);
	InputManagement->AddAction("MoveRight", this, EKeyHandler::KEY_PRESSED, &This::MoveRight);
	InputManagement->AddAction("MoveLeft", this, EKeyHandler::KEY_PRESSED, &This::MoveLeft);
}

void UPlayerController::ExitAction(float scale)
{

}

void UPlayerController::MoveForward(float scale)
{
	if (!Pawn)
		return;

	Pawn->MoveForward(scale);
}

void UPlayerController::MoveBackward(float scale)
{
	if (!Pawn)
		return;

	Pawn->MoveForward(-scale);
}

void UPlayerController::MoveRight(float scale)
{
	if (!Pawn)
		return;

	Pawn->MoveRight(-scale);
}

void UPlayerController::MoveLeft(float scale)
{
	if (!Pawn)
		return;

	Pawn->MoveRight(scale);
}
