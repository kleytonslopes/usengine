/*********************************************************************
 *   File: Model.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_MODEL_HPP
#define	US_MODEL_HPP


#include "Base/Class.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Renderer/MeshRenderer.hpp"
#include "Model-generated.hpp"

class AMesh;
class UTexture;

class UModel : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UModel();
	virtual ~UModel();

	void Initialize() override;
	void Destroy() override;

protected:
	AMesh* Target = nullptr;
	TVector<UMeshRenderer*> Meshes;
	FString DirectoryPath;

	virtual UTexture CreateTexture(const aiString& aiString, const FString& name) = 0;
	virtual UMeshRenderer* CreateMeshRenderer(aiMesh* mesh, const aiScene* scene) = 0;
private:
	TVector<UTexture> texturesLoaded;

	void SetTarget(AMesh* actor);
	void LoadModel();

	void ProcessNode(aiNode* node, const aiScene* scene);
	UMeshRenderer* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	
	TVector<UTexture> LoadMaterialTexture(aiMaterial* material, aiTextureType type, FString name);
	

	friend class AActor;
	friend class AMesh;
};

#endif // !US_MODEL_HPP