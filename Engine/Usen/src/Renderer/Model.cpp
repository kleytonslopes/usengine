/*********************************************************************
 *   File: Model.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: July 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/Model.hpp"
#include "Mesh/Mesh.hpp"
#include "Core/Vertex.hpp"

#include "Components/MeshComponent.hpp"
#include "Components/RenderComponent.hpp"

DEFAULT_BODY(UModel)

void UModel::Initialize()
{
	if (MeshActor == nullptr)
	{
		UASSERT(false, "MeshActor not found!");
	}

	RenderComponent = MeshActor->GetRenderComponent();

	Super::Initialize();
}

void UModel::SetMeshActor(AMesh* actor)
{
	this->MeshActor = actor;
}
