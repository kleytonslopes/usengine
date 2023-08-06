/*********************************************************************
 *   File: GameModeBase.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Framework/GameModeBase.hpp"
#include "Controllers/Controller.hpp"
#include "Controllers/PlayerController.hpp"
#include "Input/InputManagement.hpp"
#include "Pawns/Pawn.hpp"


UGameModeBase::UGameModeBase()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UGameModeBase::~UGameModeBase()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UGameModeBase::Create()
{
	DefaultController = UPlayerController::GetClass();
	DefaultPlayerPawn = APawn::GetClass();

	Super::Create();
}

void UGameModeBase::PostCreate()
{
	CreateController();
	CreatePlayerPawn();
}

void UGameModeBase::Initialize()
{
	Super::Initialize();

	Controller.Get()->Initialize();
}

void UGameModeBase::CreateController()
{
	Controller = USharedPtr<UController>::FromClass(DefaultController);
	Controller.Get()->Create();
}

void UGameModeBase::CreatePlayerPawn()
{
	PlayerPawn = USharedPtr<APawn>::FromClass(DefaultPlayerPawn);
	PlayerPawn.Get()->Create();
	GetInputManagement()->SetInputComponent(PlayerPawn.Get()->GetInputComponent());

	Controller.Get()->SetPawn(PlayerPawn);
}
