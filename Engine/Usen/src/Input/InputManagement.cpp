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
#include "Components/InputComponent.hpp"

UInputManagement::UInputManagement()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UInputManagement::~UInputManagement()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UInputManagement::SetInputComponent(UInputComponent* inputComponent)
{
	if (InputComponent)
		InputComponent->Deactive();

	InputComponent = inputComponent;
	InputComponent->Active();
}

void UInputManagement::RegisterAction(const FString& actionName, uint32 keyCode, float scale)
{
	ActionMap::iterator it = Actions.find(actionName);

	if (it != Actions.end())
	{
		it->second.AddInput(keyCode, scale);
		return;
	}
	
	FAction newAction{};
	newAction.AddInput(keyCode, scale);
	Actions[actionName] = newAction;
}
