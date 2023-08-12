/*********************************************************************
 *   File: Mesh.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_MESH_HPP
#define	US_MESH_HPP


#include "Actors/Actor.hpp"
#include "Mesh-generated.hpp"

class UMeshComponent;
class URenderComponent;
class UCollisionComponent;
class UModel;

struct FMeshParameters;

class AMesh : public AActor
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	void PostConstruct() override;
	void Initialize() override;
	void Update(float deltaTime) override;
	void Destroy() override;

	UMeshComponent* GetMeshComponent();
	URenderComponent* GetRenderComponent();
	UCollisionComponent* GetCollisionComponent();

	void SetMeshParameters(const FMeshParameters& parameters);
	void SetIsDynamic(const bool& isDynamic);

	void SetLocation(FVector& location) override;

protected:
	TVector<FVector> Vertices;
	TVector<uint32> Indices;

	UCollisionComponent* CollisionComponent = nullptr;
	URenderComponent* RenderComponent = nullptr;
	UMeshComponent* MeshComponent = nullptr;

	void Draw(float deltaTime) override;

private:
	UModel* Model = nullptr;
	
};

#endif // !US_MESH_HPP