/*********************************************************************
 *   File: StaticMesh.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Mesh/StaticMesh.hpp"

#include "Framework/Scene.hpp"
#include "Components/MeshComponent.hpp"
#include "Components/RendererComponent.hpp"

void UStaticMesh::OnConstruct()
{
	AddComponent<UMeshComponent>();
	AddComponent<URendererComponent>();

	Super::OnConstruct();
}

void UStaticMesh::Initialize()
{
	if (!bWasMeshParameters)
	{
		UASSERT(false, "Failed to Initialize StaticMesh. Mesh without parameters!");
	}

	UMeshComponent* meshComponent = GetComponent<UMeshComponent>();
	meshComponent->Initialize();
}

void UStaticMesh::SetMeshParameters(const FMeshParameters& parameters)
{
	if (!bWasConstructed)
	{
		UASSERT(false, "Failed to set MeshParameters. Entity not Constructed!");
	}
	UMeshComponent* meshComponent = GetComponent<UMeshComponent>();
	meshComponent->SetMeshParameters(parameters);

	bWasMeshParameters = true;
}
