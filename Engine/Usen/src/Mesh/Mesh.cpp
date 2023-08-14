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

DEFAULT_BODY(AMesh)

void AMesh::Construct()
{
	SetBoundBox(FVector{ 10.f, 10.f, 10.f });//parametrize

	Super::Construct();

	bIsDrawable = true;
	bCanUpdate = true;

	Model = FConstructorHelper::CreateObject<UModelOpenGL>();
	Model->SetMeshActor(this);

	RenderComponent = AddComponent<URenderComponent>();
	MeshComponent = AddComponent<UMeshComponent>();
	CollisionComponent = AddComponent<UBoxCollisionComponent>();
}

void AMesh::PostConstruct()
{
	Super::PostConstruct();
}

void AMesh::Initialize()
{
	Super::Initialize();

	Model->Initialize();
}

void AMesh::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (CollisionComponent && CollisionComponent->IsDynamic() /*&& Parent == nullptr*/)
	{
		FVector location = CollisionComponent->GetComponentLocation();
		SetLocation(location);
	}
}

void AMesh::Destroy()
{
	Super::Destroy();

	if(Model) Model->Destroy();

	delete Model;

	Model              = nullptr;

	RenderComponent    = nullptr;
	MeshComponent      = nullptr;
	CollisionComponent = nullptr;
}

UMeshComponent* AMesh::GetMeshComponent()
{
	return MeshComponent;
}

URenderComponent* AMesh::GetRenderComponent()
{
	return RenderComponent;
}

UCollisionComponent* AMesh::GetCollisionComponent()
{
	return CollisionComponent;
}

void AMesh::SetMeshParameters(const FMeshParameters& parameters)
{
	MeshComponent->SetMeshParameters(parameters);

	BRenderer* renderer = GetRenderer();
	BShader* shader = renderer->GetShader(parameters.ShaderName);

	RenderComponent->SetShader(shader);
}

void AMesh::SetIsDynamic(const bool& isDynamic)
{
	if (CollisionComponent)
		CollisionComponent->SetIsDynamic(isDynamic);
}

void AMesh::SetCollisionGroup(ECollisionGroup collisionGroup)
{
	if (CollisionComponent)
		CollisionComponent->SetCollisionGroup(collisionGroup);
}

void AMesh::SetCollisionMask(ECollisionMask collisionMask)
{
	if (CollisionComponent)
		CollisionComponent->SetCollisionMask(collisionMask);
}

void AMesh::SetTransform(FTransform& transform)
{
	Super::SetTransform(transform);

	if (!CollisionComponent->IsDynamic())
	{
		CollisionComponent->SetLocation(GetLocation());
	}
}

void AMesh::SetLocation(FVector& location)
{
	Super::SetLocation(location);

	if (!CollisionComponent->IsDynamic())
	{
		CollisionComponent->SetLocation(GetLocation());
	}
}

void AMesh::SetBoundBox(const FVector& boundBox)
{
	BoundBox.x = boundBox.x;
	BoundBox.y = boundBox.y;
	BoundBox.z = boundBox.z;
}

void AMesh::Draw(float deltaTime)
{
	if(bIsDrawable)
		Model->Draw(deltaTime);
}
