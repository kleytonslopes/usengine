/*********************************************************************
 *   File: Mesh.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Mesh/Mesh.hpp"
#include "Components/RenderComponent.hpp"
#include "Components/MeshComponent.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/OpenGL/ModelOpenGL.hpp"

AMesh::AMesh()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

AMesh::~AMesh()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void AMesh::Create()
{
	Super::Create();

	Model = UUniquePtr<UModel>::MakeCast<UModelOpenGL>();
	Model.Get()->SetMeshActor(this);

	URenderComponent* RenderComponent = AddComponent<URenderComponent>();
	RenderComponent->SetOwner(Owner);
	RenderComponent->SetParent(this);

	UMeshComponent* MeshComponent = AddComponent<UMeshComponent>();
	MeshComponent->SetOwner(Owner);
	MeshComponent->SetParent(this);

	PostCreate();
}

void AMesh::PostCreate()
{

}

void AMesh::Initialize()
{
	Model.Get()->Initialize();
}

UMeshComponent* AMesh::GetMeshComponent()
{
	return GetComponent<UMeshComponent>();
}

void AMesh::SetMeshParameters(const FMeshParameters& parameters)
{
	UMeshComponent* MeshComponent = GetMeshComponent();
	MeshComponent->SetMeshParameters(parameters);
}
