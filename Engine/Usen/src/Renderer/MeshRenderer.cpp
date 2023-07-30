/*********************************************************************
 *   File: MeshRenderer.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/MeshRenderer.hpp"
#include "Renderer/Texture.hpp"
#include "Core/Vertex.hpp"

UMeshRenderer::UMeshRenderer()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UMeshRenderer::~UMeshRenderer()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UMeshRenderer::Initialize()
{
	Super::Initialize();

	CreateVAO();
	CreateVBO();
	CreateEBO();
	CreateFBO();
}

void UMeshRenderer::CreateMeshRenderer(aiMesh* mesh, const aiScene* scene)
{
	for (uint32 i = 0; i < mesh->mNumVertices; i++)
	{
		FVertex vertex;

		FVector vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normals = vector;
		}

		if (mesh->mTextureCoords[0])
		{
			FVector2 uvect;
			uvect.x = mesh->mTextureCoords[0][i].x;
			uvect.y = mesh->mTextureCoords[0][i].y;
			vertex.UV = uvect;
		}
		else
			vertex.UV = FVector2{ 0.f, 0.f };

		vertices.push_back(vertex);
	}

	/* Process Indices */
	for (uint32 i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (uint32 f = 0; f < face.mNumIndices; f++)
		{
			indices.push_back(face.mIndices[f]);
		}
	}
}
