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
#include "Renderer/OpenGL/ShaderOpenGL.hpp"
#include "Renderer/OpenGL/TextureOpenGL.hpp"

#include "Renderer/Texture.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Model.hpp"

#include "Core/Vertex.hpp"

#include <glad/glad.h>

UMeshRendererOpenGL::UMeshRendererOpenGL()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UMeshRendererOpenGL::~UMeshRendererOpenGL()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UMeshRendererOpenGL::Setup(TVector<FVertex> vertices, TVector<uint32> indices, TVector<UTextureOpenGL> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	CreateVAO();
	CreateVBO();
	CreateEBO();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex), reinterpret_cast<void*>(offsetof(FVertex, Position)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex), reinterpret_cast<void*>(offsetof(FVertex, UV)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex), reinterpret_cast<void*>(offsetof(FVertex, Normals)));
	glEnableVertexAttribArray(2);


	glBindVertexArray(0);
}

void UMeshRendererOpenGL::Draw(FVector location, FVector rotation, FVector scale)
{
	uint32 diffuseNr = 1;
	uint32 specularNr = 1;
	uint32 normalNr = 1;
	uint32 heightNr = 1;

	FMatrix4 matrix = FMatrix4{ 1.f };

	//matrix = glm::translate(FMatrix4{ 1.f }, location);
	//matrix = glm::rotate(FMatrix4{ 1.f }, glm::radians(rotation.x), FVector{1.f, 0.f, 0.f});
	//matrix = glm::rotate(FMatrix4{ 1.f }, glm::radians(rotation.y), FVector{0.f, 1.f, 0.f});
	//matrix = glm::rotate(FMatrix4{ 1.f }, glm::radians(rotation.z), FVector{0.f, 0.f, 1.f});
	//matrix = glm::scale(FMatrix4{ 1.f }, scale);

	matrix = glm::translate(matrix, location);
	matrix = glm::rotate(matrix, glm::radians(rotation.x), FVector{ 1.f, 0.f, 0.f });
	matrix = glm::rotate(matrix, glm::radians(rotation.y), FVector{ 0.f, 1.f, 0.f });
	matrix = glm::rotate(matrix, glm::radians(rotation.z), FVector{ 0.f, 0.f, 1.f });
	matrix = glm::scale(matrix, scale);

	Shader->Active();
	Shader->SetMatrix4("model", matrix);
	//Shader->SetMatrix4("cameraPos", matrix);

	for (uint32 i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		FString number;
		FString name = textures[i].Type;

		if (name == TextureSlot::DIFFUSE)
			number = std::to_string(diffuseNr++);
		else if(name == TextureSlot::SPECULAR)
			number = std::to_string(specularNr++);
		else if (name == TextureSlot::NORMAL)
			number = std::to_string(normalNr++);
		else if (name == TextureSlot::HEIGHT)
			number = std::to_string(heightNr++);

		glUniform1i(glGetUniformLocation(Shader->GetProgramId(), (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].Id);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
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
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		glGenTextures(1, &fboTexture);
		glBindTexture(GL_TEXTURE_2D, fboTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTexture, 0);
	}
}
