/*********************************************************************
 *   File: MeshComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Components/MeshComponent.hpp"

DEFAULT_BODY(UMeshComponent)

void UMeshComponent::SetMeshParameters(const FMeshParameters& parameters)
{
	Parameters.MeshPath = parameters.MeshPath;
}

void UMeshComponent::Serialize(SeriFile& otherOut)
{
	BeginComponentSection(otherOut, Identity);

	Key(otherOut, "mesh_path", Parameters.MeshPath);

	EndSection(otherOut);
}

FString UMeshComponent::GetModelPath() const
{
	return Parameters.MeshPath;
}
