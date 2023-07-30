/*********************************************************************
 *   File: ModelOpenGL.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: July 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/OpenGL/ModelOpenGL.hpp"
#include "Renderer/OpenGL/TextureOpenGL.hpp"
#include "Renderer/MeshRenderer.hpp"
#include "Renderer/OpenGL/MeshRendererOpenGL.hpp"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

UModelOpenGL::UModelOpenGL()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UModelOpenGL::~UModelOpenGL()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UModelOpenGL::Initialize()
{
	if (!Target)
	{
		UASSERT(false, "Target of model not created!");
	}

	Super::Initialize();
}

UTexture UModelOpenGL::CreateTexture(const aiString& aiString, const FString& typeName)
{
	UTextureOpenGL texture{};
	texture.Id = TextureFromFile(aiString.C_Str(), DirectoryPath);
	texture.Type = typeName;
	texture.Path = aiString.C_Str();

	return texture;
}

uint32 UModelOpenGL::TextureFromFile(UCharPtr filePath, const FString& directory, bool gamma)
{
	FString fileName = FString(filePath);
	fileName = DirectoryPath + '/' + fileName;

	uint32 textureId;
	glGenTextures(1, &textureId);

	int width, height, nrComponents;
	UUCharPtr data = stbi_load(fileName.c_str(), &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format;

		//if (nrComponents == 1)
		//	format == GL_RED;
		//else if (nrComponents == 3)
		//	format == GL_RGB;
		//else if (nrComponents == 4)
			format == GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		ULOG_Error(FText::Format("Failed to load texture at path: %s", filePath));
		stbi_image_free(data);
	}
	return textureId;
}

UMeshRenderer* UModelOpenGL::CreateMeshRenderer(aiMesh* mesh, const aiScene* scene)
{
	UMeshRendererOpenGL* meshRenderer = new UMeshRendererOpenGL();
	meshRenderer->CreateMeshRenderer(mesh, scene);
	//meshRenderer.vertices = vertices;
	//meshRenderer.indices = indices;
	//meshRenderer.textures = texturesLoaded;

	return meshRenderer;
}
