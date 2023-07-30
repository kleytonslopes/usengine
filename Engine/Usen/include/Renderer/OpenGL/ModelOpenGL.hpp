/*********************************************************************
 *   File: ModelOpenGL.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_MODEL_OPEN_GL_HPP
#define	US_MODEL_OPEN_GL_HPP


#include "Renderer/Model.hpp"
#include "ModelOpenGL-generated.hpp"

class UModelOpenGL : public UModel
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UModelOpenGL();
	~UModelOpenGL() final;

	void Initialize() override;

protected:
	UTexture CreateTexture(const aiString& aiString, const FString& typeName) override;

	uint32 TextureFromFile(UCharPtr filePath, const FString& directory, bool gamma = false);
	UMeshRenderer* CreateMeshRenderer(aiMesh* mesh, const aiScene* scene) override;
};

#endif // !US_MODEL_OPEN_GL_HPP