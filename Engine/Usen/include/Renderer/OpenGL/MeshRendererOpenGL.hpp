/*********************************************************************
 *   File: MeshRendererOpenGL.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_MESH_RENDERER_OPEN_GL_HPP
#define	US_MESH_RENDERER_OPEN_GL_HPP


#include "Renderer/MeshRenderer.hpp"
#include "MeshRendererOpenGL-generated.hpp"

class UTextureOpenGL;

class UMeshRendererOpenGL : public UMeshRenderer
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UMeshRendererOpenGL();
	virtual ~UMeshRendererOpenGL();

	void Setup(TVector<FVertex> vertices, TVector<uint32> indices, TVector<UTextureOpenGL> textures);

	void CreateVAO();
	void CreateVBO();
	void CreateEBO();
	void CreateFBO();

private:
	TVector<FVertex> vertices;
	TVector<uint32> indices;
	TVector<UTextureOpenGL> textures;

	uint32 fboTexture;

	uint32 VAO;
	uint32 VBO;
	uint32 EBO;
	uint32 FBO;
};

#endif // !US_MESH_RENDERER_OPEN_GL_HPP