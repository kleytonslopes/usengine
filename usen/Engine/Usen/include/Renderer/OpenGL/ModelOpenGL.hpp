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

class UMeshRendererOpenGL;
class UTextureOpenGL;
class UShaderOpenGL;

class UModelOpenGL : public UModel
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UModelOpenGL();
	~UModelOpenGL() final;

	void Initialize() override;
	void LoadModel() override;
	void Draw(float deltaTime) override;

private:
	TVector<UMeshRendererOpenGL> Meshes;
	TVector<UTextureOpenGL> texturesLoaded;
	UShaderOpenGL* Shader = nullptr;

	void ProcessNode(aiNode* node, const aiScene* scene);
	UMeshRendererOpenGL ProcessMesh(aiMesh* mesh, const aiScene* scene);
	TVector<UTextureOpenGL> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, FString typeName);
	uint32 TextureFromFile(UCharPtr path, const FString& directory, bool gamma = false);

	friend class UMeshRendererOpenGL;
};

#endif // !US_MODEL_OPEN_GL_HPP