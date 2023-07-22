/*********************************************************************
 *   File: RendererComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Components/RendererComponent.hpp"

void URendererComponent::Initialize()
{
	Super::Initialize();
}

void URendererComponent::Serialize(YAML::Emitter& otherOut)
{
	BeginComponentMap(otherOut, "URendererComponent");

	EndMap(otherOut);
}

bool URendererComponent::Deserialize(const FString& scenePath)
{
	return false;
}
