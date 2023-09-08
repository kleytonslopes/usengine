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

bool UInputComponent::ExecuteAxisAction(const FString& action, EKeyHandler keyHandler)
{
	FString localAction = keyHandler == EKeyHandler::KEY_PRESSED ? action + "_Pressed" : action + "_Released";
	
	AxisActionMap::iterator it;
	it = AxisActions.find(localAction);
	if (it != AxisActions.end())
	{
		it->second.Execute.Broadcast(1.f);
		return true;
	}
	return false;
}

bool UInputComponent::ExecuteVoidAction(const FString& action, EKeyHandler keyHandler)
{
	FString localAction = keyHandler == EKeyHandler::KEY_PRESSED ? action + "_Pressed" : action + "_Released";

	VoidActionMap::iterator it;
	it = VoidActions.find(localAction);
	if (it != VoidActions.end())
	{
		it->second.Execute.Broadcast();
		return true;
	}
	return false;
}

void UInputComponent::Active()
{
	bIsActive = true;
}

void UInputComponent::Deactive()
{
	bIsActive = false;
}
