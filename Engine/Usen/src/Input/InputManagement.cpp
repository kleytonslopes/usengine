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

UInputManagement::UInputManagement()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UInputManagement::~UInputManagement()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UInputManagement::Create()
{
	GetWindow()->OnKeyEvent.Add(this, &This::OnKeyEvent);

	RegisteredKeys[27] = "Exit";

	Super::Create();
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
		InputComponent->ExecuteAction(it->second.c_str(), keyHandler);
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
