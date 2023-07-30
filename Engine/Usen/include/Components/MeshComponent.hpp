/*********************************************************************
 *   File: MeshComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_MESH_COMPONENT_HPP
#define	US_MESH_COMPONENT_HPP


#include "Components/Component.hpp"
#include "MeshComponent-generated.hpp"

struct FMeshParameters
{
	FString MeshPath;
};

class UMeshComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UMeshComponent();
	virtual ~UMeshComponent();

	void SetMeshParameters(const FMeshParameters& parameters);

protected:
	void Serialize(SeriFile& otherOut) override;

private:
	FMeshParameters Parameters;

	FString GetModelPath() const;

	friend class UModel;
};

#endif // !US_MESH_COMPONENT_HPP