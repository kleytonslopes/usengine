/*********************************************************************
 *   File: MeshRenderer.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_MESH_RENDERER_HPP
#define	US_MESH_RENDERER_HPP


#include "Base/Class.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "MeshRenderer-generated.hpp"

class FVertex;
class UTexture;

class UMeshRenderer : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UMeshRenderer();
	virtual ~UMeshRenderer();
};

#endif // !US_MESH_RENDERER_HPP