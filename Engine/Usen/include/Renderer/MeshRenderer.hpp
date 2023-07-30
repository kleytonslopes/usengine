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

	void Initialize() override;
	virtual void CreateMeshRenderer(aiMesh* mesh, const aiScene* scene);

protected:
	TVector<FVertex> vertices;
	TVector<uint32> indices;
	TVector<UTexture> textures;

	virtual void CreateVAO() { /* override */}
	virtual void CreateVBO() { /* override */}
	virtual void CreateEBO() { /* override */}
	virtual void CreateFBO() { /* override */}

	friend class UModelOpenGL;

};

#endif // !US_MESH_RENDERER_HPP