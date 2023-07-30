/*********************************************************************
 *   File: MeshRendererOpenGL.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/OpenGL/MeshRendererOpenGL.hpp"
#include "Core/Vertex.hpp"
#include "Renderer/Texture.hpp"
#include <glad/glad.h>

UMeshRendererOpenGL::UMeshRendererOpenGL()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UMeshRendererOpenGL::~UMeshRendererOpenGL()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UMeshRendererOpenGL::Destroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &EBO);
	glDeleteBuffers(1, &FBO);
}

void UMeshRendererOpenGL::Initialize()
{
	Super::Initialize();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex), reinterpret_cast<void*>(offsetof(FVertex, Position)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex), reinterpret_cast<void*>(offsetof(FVertex, UV)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex), reinterpret_cast<void*>(offsetof(FVertex, Normals)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void UMeshRendererOpenGL::CreateMeshRenderer(aiMesh* mesh, const aiScene* scene)
{
	Super::CreateMeshRenderer(mesh, scene);
}

void UMeshRendererOpenGL::CreateVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void UMeshRendererOpenGL::CreateVBO()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(FVertex), &vertices[0], GL_STATIC_DRAW);
}

void UMeshRendererOpenGL::CreateEBO()
{
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void UMeshRendererOpenGL::CreateFBO()
{
	//glGenFramebuffers(1, &FBO);
	//glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	//{
	//	glGenTextures(1, &fboTexture);
	//	glBindTexture(GL_TEXTURE_2D, fboTexture);
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTexture, 0);
	//}
}
