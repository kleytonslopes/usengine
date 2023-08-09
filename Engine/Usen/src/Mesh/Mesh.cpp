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
#include "Components/CollisionComponent.hpp"
#include "Components/BoxCollisionComponent.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/OpenGL/ModelOpenGL.hpp"
#include "Renderer/Renderer.hpp"

AMesh::AMesh()
{
}

AMesh::~AMesh()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void AMesh::Create()
{
	Super::Create();

	Model = UUniquePtr<UModel>::MakeCast<UModelOpenGL>();
	Model.Get()->Construct();
	Model.Get()->Create();
	Model.Get()->SetMeshActor(this);

	URenderComponent* RenderComponent = AddComponent<URenderComponent>();
	RenderComponent->SetOwner(Owner);
	RenderComponent->SetParent(this);

	UMeshComponent* MeshComponent = AddComponent<UMeshComponent>();
	MeshComponent->SetOwner(Owner);
	MeshComponent->SetParent(this);

	CollisionComponent = AddComponent<UBoxCollisionComponent>();
	CollisionComponent->SetOwner(Owner);
	CollisionComponent->SetParent(this);
}

void AMesh::PostCreate()
{
	
}

void AMesh::Initialize()
{
	Model.Get()->Initialize();
}

void AMesh::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (CollisionComponent && CollisionComponent->IsDynamic() && Parent == nullptr)
	{
		SetLocation(CollisionComponent->GetLocation());
	}
}

UMeshComponent* AMesh::GetMeshComponent()
{
	return GetComponent<UMeshComponent>();
}

URenderComponent* AMesh::GetRenderComponent()
{
	return GetComponent<URenderComponent>();
}

UCollisionComponent* AMesh::GetCollisionComponent()
{
	return GetComponent<UCollisionComponent>();
}

void AMesh::SetMeshParameters(const FMeshParameters& parameters)
{
	UMeshComponent* MeshComponent = GetMeshComponent();
	MeshComponent->SetMeshParameters(parameters);

	BRenderer* renderer = GetRenderer();
	BShader* shader = renderer->GetShader(parameters.ShaderName);

	URenderComponent* RenderComponent = GetRenderComponent();
	RenderComponent->SetShader(shader);
}

void AMesh::SetIsDynamic(const bool& isDynamic)
{
	if (CollisionComponent)
		CollisionComponent->SetIsDynamic(isDynamic);
}

void AMesh::Draw(float deltaTime)
{

	Model.Get()->Draw(deltaTime);
}
