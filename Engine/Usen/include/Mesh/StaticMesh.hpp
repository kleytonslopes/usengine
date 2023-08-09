/*********************************************************************
 *   File: StaticMesh.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_STATIC_MESH_HPP
#define	US_STATIC_MESH_HPP


#include "Mesh/Mesh.hpp"
#include "StaticMesh-generated.hpp"

class UStaticMesh : public AMesh
{
	DEFAULT_BODY_GENERATED()
public:

	void Create() override;
};

#endif // !US_STATIC_MESH_HPP