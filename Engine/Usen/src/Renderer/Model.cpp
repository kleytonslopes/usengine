/*********************************************************************
 *   File: Model.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: July 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/Model.hpp"
#include "Mesh/Mesh.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/OpenGL/TextureOpenGL.hpp"
#include "Core/Vertex.hpp"

#include "Components/MeshComponent.hpp"

UModel::UModel()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UModel::~UModel()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UModel::Initialize()
{
	Super::Initialize();

	if (!Target)
		return;

	LoadModel();
	for (UMeshRenderer* meshR : Meshes)
	{
		meshR->Initialize();
	}
}

void UModel::Destroy()
{
	Super::Destroy();

	for (uint32 i = 0; i < Meshes.size(); i++)
	{
		Meshes[i]->Destroy();
		delete Meshes[i];
	}
}

void UModel::SetTarget(AMesh* actor)
{
	Target = actor;
}

void UModel::LoadModel()
{
	Assimp::Importer importer;

	UMeshComponent* MeshComponent = Target->GetMeshComponent();

	if (MeshComponent == nullptr)
	{
		UASSERT(false, "Model without MeshComponent");
	}

	FString modPath = MeshComponent->GetModelPath();

	const aiScene* scene = importer.ReadFile(MeshComponent->GetModelPath(), aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		UASSERT(false, FText::Format("ERRO::ASSIMP::%s", importer.GetErrorString()).c_str());
		return;
	}

	DirectoryPath = MeshComponent->GetModelPath().substr(0, MeshComponent->GetModelPath().find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void UModel::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (uint32 i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (uint32 i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

UMeshRenderer* UModel::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	UMeshRenderer* newMesh = CreateMeshRenderer(mesh, scene);

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	TVector<UTexture> defuse = LoadMaterialTexture(material, aiTextureType_DIFFUSE, "diffuse");

	return newMesh;
}

TVector<UTexture> UModel::LoadMaterialTexture(aiMaterial* material, aiTextureType type, FString name)
{
	TVector<UTexture> textures;
	for (uint32 i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);
		bool skip = false;

		for (uint32 t = 0; t < texturesLoaded.size(); t++)
		{
			if (std::strcmp(texturesLoaded[t].GetPath(), str.C_Str()) == 0)
			{
				textures.push_back(texturesLoaded[t]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			UTexture texture = CreateTexture(str, name);
			textures.push_back(texture);
			texturesLoaded.push_back(texture);
		}
	}
	return textures;
}
