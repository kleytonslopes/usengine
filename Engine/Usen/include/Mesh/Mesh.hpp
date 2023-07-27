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
struct FMeshParameters;

class AMesh : public AActor
{
	DEFAULT_BODY_GENERATED()
public:
	explicit AMesh();
	virtual ~AMesh();

	void Create() override;

	UMeshComponent* GetMeshComponent();

	void SetMeshParameters(const FMeshParameters& parameters);

protected:
	TVector<FVector> Vertices;
	TVector<uint32> Indices;
};

#endif // !US_MESH_HPP