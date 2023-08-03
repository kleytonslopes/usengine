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

UMeshComponent::UMeshComponent()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UMeshComponent::~UMeshComponent()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

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
