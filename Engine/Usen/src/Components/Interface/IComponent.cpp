/*********************************************************************
 *   File: IComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Components/Interface/IComponent.hpp"
#include "Core/Guid.hpp"
#include "Framework/Entity.hpp"

IComponent::IComponent(UEntity* Parent) 
	: Parent{ Parent }
{
	Id = FGuid::NewGuid();
}

IComponent::~IComponent()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("Component '%s' Destroyed!", Id.c_str()));
}

void IComponent::Initialize()
{
	if (!GetParent())
	{
		UASSERT(false, "Component does not have Owner!");
	}
}

UEntity* IComponent::GetParent()
{
	return Parent;
}
