/*********************************************************************
 *   File: StaticMesh.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_STATIC_MESH_HPP
#define	US_STATIC_MESH_HPP

#include "Framework/Entity.hpp"

class UStaticMesh : public UEntity
{
	DEFAULT_BODY(UEntity);

public:
	// Inherited via UEntity
	void OnConstruct() override;
	void Initialize() override;

	void SetMeshParameters(const FMeshParameters& parameters);

private:
	bool bWasMeshParameters = false;

};

#endif // !US_STATIC_MESH_HPP