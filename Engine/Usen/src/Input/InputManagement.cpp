/*********************************************************************
 *   File: InputManagement.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
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
