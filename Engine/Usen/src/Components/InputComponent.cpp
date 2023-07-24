/*********************************************************************
 *   File: InputComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Components/InputComponent.hpp"

UInputComponent::UInputComponent()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UInputComponent::~UInputComponent()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UInputComponent::Active()
{
	bIsActive = true;
}

void UInputComponent::Deactive()
{
	bIsActive = false;
}
