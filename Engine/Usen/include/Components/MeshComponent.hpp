/*********************************************************************
 *   File: MeshComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_MESH_COMPONENT_HPP
#define	US_MESH_COMPONENT_HPP

#include "Components/Interface/IComponent.hpp"

struct FMeshParameters
{
	FString MeshPath;
};

class UMeshComponent : public IComponent
{
	DEFAULT_BODY(IComponent);
public:
	void Initialize() override;

	void SetMeshParameters(const FMeshParameters& parameters);

private:
	FMeshParameters parameters;
};

#endif // !US_MESH_COMPONENT_HPP