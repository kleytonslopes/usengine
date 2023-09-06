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
	SetBoundBox(FVector{ 1.f, 1.f, 1.f });

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

	if (CollisionComponent)
	{
		CollisionComponent->SetLocation(GetLocation());
	}

	Model->Initialize();
}

void AMesh::Update(float deltaTime)
{
	Super::Update(deltaTime);
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
	{
		CollisionComponent->SetIsDynamic(isDynamic);
		CollisionComponent->SetBodyType(EBodyType::EBT_Static);
	}
}

void AMesh::SetCanCollider(const bool& canCollider)
{
	CollisionComponent->SetCanCollider(canCollider);
}

void AMesh::RemoveCollisionComponent()
{
	if (CollisionComponent)
	{
		bool hasRemoved = RemoveComponent<UBoxCollisionComponent>();
		if (hasRemoved)
		{
			delete CollisionComponent;
			CollisionComponent = nullptr;
		}
	}
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

FVector AMesh::GetBoundBox() const
{
	if (CollisionComponent)
	{
		return CollisionComponent->GetBoundBox();
	}
	return FVector(0.f);
}

void AMesh::SetBoundBox(const FVector& boundBox)
{
	if (CollisionComponent)
	{
		CollisionComponent->SetBoundBox(boundBox);
	}
}

void AMesh::Draw(float deltaTime)
{
	if(bIsDrawable)
		Model->Draw(deltaTime);
}
