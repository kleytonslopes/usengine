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

UPlayerController::UPlayerController()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UPlayerController::~UPlayerController()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UPlayerController::Initialize()
{
	Super::Initialize();

	SetupInputComponent();
}

void UPlayerController::Create()
{
	Super::Create();
}

void UPlayerController::SetupInputComponent()
{
	UInputManagement* InputManagement = GetInputManagement();

	InputManagement->AddAction("Exit", this, EKeyHandler::KEY_PRESSED, &This::ExitAction);
}

void UPlayerController::ExitAction(float scale)
{

}
