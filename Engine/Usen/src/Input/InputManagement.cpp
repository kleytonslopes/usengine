/*********************************************************************
 *   File: InputManagement.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Input/InputManagement.hpp"
#include "Presentation/Window.hpp"
#include "Components/InputComponent.hpp"
#include "Runtime/Application.hpp"
#include "Configs/EngineConfig.hpp"

DEFAULT_BODY(UInputManagement)

void UInputManagement::Construct()
{
	Super::Construct();
}

void UInputManagement::PostConstruct()
{
	GetWindow()->OnKeyEvent.Add(this, &This::OnKeyEvent);
	GetApplication()->OnUpdateEvent.Add(this, &This::Update);

	FEngineConfig engineConfig{};

	engineConfig.LoadConfig();
	TMap<uint32, FString> keysBinds = engineConfig.GetKeyBinds();

	for (const auto& it : keysBinds)
	{
		FKeyMap kb{};
		kb.ActionName = it.second;
		kb.KeyCode = it.first;

		RegisteredKeys[it.first] = kb;
	}

	Super::PostConstruct();
}

void UInputManagement::Update(float deltaTime)
{
	Super::Update(deltaTime);

	//KeyMap::iterator it;

	for (auto& it : RegisteredKeys)
	{
		if (it.second.bIsPressed)
		{
			InputComponent->ExecuteAction(it.second.ActionName.c_str(), EKeyHandler::KEY_PRESSED);
		}
	}
}

void UInputManagement::SetInputComponent(UInputComponent* inputComponent)
{
	if (InputComponent)
		InputComponent->Deactive();

	InputComponent = inputComponent;
	InputComponent->Active();
}

void UInputManagement::OnKeyEvent(uint32 keyCode, EKeyHandler keyHandler)
{
	if (!InputComponent)
		return;

	KeyMap::iterator it;

	it = RegisteredKeys.find(keyCode);
	
	if (it != RegisteredKeys.end())
	{

		it->second.bIsPressed = keyHandler == EKeyHandler::KEY_PRESSED ? true : false;
		//InputComponent->ExecuteAction(it->second.c_str(), keyHandler);
	}
}

void UInputManagement::RegisterAction(uint32 keyCode, const FString& actionName)
{
	ActionMap::iterator it = Actions.find(actionName);

	if (it != Actions.end())
	{
		it->second.AddInput(keyCode, actionName);
		return;
	}
	
	FAction newAction{};
	newAction.AddInput(keyCode, actionName);
	Actions[actionName] = newAction;
}
