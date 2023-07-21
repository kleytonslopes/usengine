/*********************************************************************
 *   File: MeshComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Components/MeshComponent.hpp"
#include "Framework/Entity.hpp"

void UMeshComponent::Initialize()
{
	Super::Initialize();
	/* Load Model */
}

void UMeshComponent::SetMeshParameters(const FMeshParameters& parameters)
{
	this->parameters = parameters;
}
