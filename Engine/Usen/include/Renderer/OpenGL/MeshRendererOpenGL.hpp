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

class UMeshRendererOpenGL : public UMeshRenderer
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UMeshRendererOpenGL();
	virtual ~UMeshRendererOpenGL();

	void Destroy() final;

	void Initialize() override;
	void CreateMeshRenderer(aiMesh* mesh, const aiScene* scene) override;

protected:
	uint32 VAO;
	uint32 VBO;
	uint32 EBO;
	uint32 FBO;
	uint32 fboTexture;

	void CreateVAO() override;
	void CreateVBO() override;
	void CreateEBO() override;
	void CreateFBO() override;

	friend class UModelOpenGL;

};

#endif // !US_MESH_RENDERER_OPEN_GL_HPP