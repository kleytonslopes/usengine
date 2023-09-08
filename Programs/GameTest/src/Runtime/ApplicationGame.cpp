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
#include "Presentation/Window.hpp"

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

	Window->OnMouseButtonEvent.Add(this, &This::OnMouseButtonEvent);
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

void UApplicationGame::OnMouseButtonEvent(uint32 keyCode, EKeyHandler keyHandler)
{
	if (keyCode == 3)
	{
		switch (keyHandler)
		{
		case KEY_NONE:
			break;
		case KEY_PRESSED:
			Window->SetMouseLocked(true);
			break;
		case KEY_RELEASED:
			Window->SetMouseLocked(false);
			break;
		default:
			break;
		}
	}
}
