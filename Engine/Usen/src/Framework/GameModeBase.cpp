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
#include "Pawns/Character.hpp"

DEFAULT_BODY(UGameModeBase)

void UGameModeBase::Construct()
{
	FConstructorHelper::MakeClassOf<UPlayerController>(DefaultController);
	//FConstructorHelper::MakeClassOf<ACharacter>(DefaultPlayerPawn);

	Super::Construct();
}

void UGameModeBase::Initialize()
{

	Super::Initialize();
}

TClassOf<APawn> UGameModeBase::GetDefaultPlayerPawn()
{
	return DefaultPlayerPawn;
}

TClassOf<UController> UGameModeBase::GetDefaultController()
{
	return DefaultController;
}

void UGameModeBase::SetController(UController* controller)
{
	Controller = controller;
}

void UGameModeBase::SetPlayerPawn(APawn* playerPawn)
{
	PlayerPawn = playerPawn;
}
