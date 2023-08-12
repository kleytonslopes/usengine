/*********************************************************************
 *   File: InputComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Presentation/Window.hpp"
#include "Components/InputComponent.hpp"

DEFAULT_BODY(UInputComponent)

void UInputComponent::Construct()
{
	Super::Construct();
}

void UInputComponent::ExecuteAction(const FString& action, EKeyHandler keyHandler)
{
	FString localAction = keyHandler == EKeyHandler::KEY_PRESSED ? action + "_Pressed" : action + "_Released";
	
	ActionMap::iterator it;
	it = Actions.find(localAction);
	if (it != Actions.end())
	{
		it->second.Execute.Broadcast(1.f);
	}
}

void UInputComponent::Active()
{
	bIsActive = true;
}

void UInputComponent::Deactive()
{
	bIsActive = false;
}
