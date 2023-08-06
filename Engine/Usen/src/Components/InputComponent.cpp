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

UInputComponent::UInputComponent()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UInputComponent::~UInputComponent()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UInputComponent::Create()
{

}

void UInputComponent::ExecuteAction(const FString& action, EKeyHandler keyHandler)
{
	FString localAction = keyHandler == EKeyHandler::KEY_PRESSED ? action + "_Pressed" : action + "_Released";
	
	ULOG(ELogLevel::ELL_DEBUG, FText::Format("Finding Action %s...", localAction.c_str()));

	ActionMap::iterator it;
	it = Actions.find(localAction);
	if (it != Actions.end())
	{
		it->second.Execute.Broadcast(1.f);
		ULOG(ELogLevel::ELL_DEBUG, FText::Format("Action %s Executed!", localAction.c_str()));
	}
	else
		ULOG(ELogLevel::ELL_DEBUG, FText::Format("Action %s Not found!", localAction.c_str()));
}

void UInputComponent::Active()
{
	bIsActive = true;
}

void UInputComponent::Deactive()
{
	bIsActive = false;
}
