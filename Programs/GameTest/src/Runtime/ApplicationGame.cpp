/*********************************************************************
 *   File: ApplicationGame.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Runtime/ApplicationGame.hpp"
#include "Framework/TestGameInstance.hpp"

DEFAULT_BODY(UApplicationGame)

void UApplicationGame::Construct()
{
	Super::Construct();

	FConstructorHelper::MakeClassOf<URendererOpenGL>(DefaultRenderer);
	FConstructorHelper::MakeClassOf<UTestGameInstance>(DefaultGameInstance);
}

void UApplicationGame::PostConstruct()
{
	Super::PostConstruct();

	GameInstance = FConstructorHelper::CreateObject<UTestGameInstance>();
}

void UApplicationGame::Initialize()
{
	Super::Initialize();
}

void UApplicationGame::Destroy()
{
	Super::Destroy();
}

void UApplicationGame::Draw(float deltaTime)
{
	Super::Draw(deltaTime);
}
