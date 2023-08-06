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
	explicit AMesh();
	virtual ~AMesh();

	void Create() override;
	void PostCreate() override;
	void Initialize() override;
	void Update(float deltaTime) override;

	UMeshComponent* GetMeshComponent();
	URenderComponent* GetRenderComponent();
	UCollisionComponent* GetCollisionComponent();

	void SetMeshParameters(const FMeshParameters& parameters);
	void SetIsDynamic(const bool& isDynamic);

protected:
	TVector<FVector> Vertices;
	TVector<uint32> Indices;
	UCollisionComponent* CollisionComponent = nullptr;

	void Draw(float deltaTime) override;

private:
	UUniquePtr<UModel> Model;
	
};

#endif // !US_MESH_HPP