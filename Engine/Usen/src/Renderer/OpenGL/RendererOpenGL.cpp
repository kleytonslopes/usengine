/*********************************************************************
 *   File: RendererOpenGL.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/OpenGL/RendererOpenGL.hpp"

#include "Framework/GameInstance.hpp"
#include "Framework/Scene.hpp"
#include "Camera/Camera.hpp"

#include <glad/glad.h>

#include "Presentation/Window.hpp"

DEFAULT_BODY(URendererOpenGL)

void URendererOpenGL::Initialize()
{
	GetWindow()->OnWindowResizedEvent.Add(this, &This::OnWindowResize);
	glViewport(0, 0, GetWindow()->GetWidth(), GetWindow()->GetHeight());

	glEnable(GL_MULTISAMPLE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	Super::Initialize();
}

void URendererOpenGL::StartFrame()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	ACamera* Camera = GetScene()->GetCamera();
	FVector cameraPos = Camera->GetLocation();

	UWindow* window = GetWindow();
	FMatrix4 projection = glm::perspective(glm::radians(45.0f), (float)window->GetWidth() / (float)window->GetHeight(), 0.001f, 10000.0f);
	FMatrix4 view = Camera->GetView();
	
	FMatrix4 modelMatrix = FMatrix4{ 1.f };//veresse
	glm::vec3 loc {0.0f, 0.0f, 0.0f};
	glm::vec3 sca {1.0f, 1.0f, 1.0f};
	modelMatrix = glm::translate(modelMatrix, loc);
	modelMatrix = glm::scale(modelMatrix, sca);

	TMap<FString, BShader*>::iterator shdIterator;

	for (shdIterator = Shaders.begin(); shdIterator != Shaders.end(); shdIterator++)
	{
		shdIterator->second->Active();
		shdIterator->second->SetMatrix4("projection", projection);
		shdIterator->second->SetMatrix4("view", view);
		shdIterator->second->SetMatrix4("model", modelMatrix);
		shdIterator->second->Deactive();
	}
	
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	//FVector fromVec2 = FVector{ 0.f };
	//FVector toVec2 = FVector{ 7.f,0.f,10.f };
	//DebugDrawLine(fromVec2, toVec2);

	//DebugDrawLine(FVector{ 0.f, 0.f, 0.f }, FVector{ 0.f, 0.f, 10.f });
}

void URendererOpenGL::EndFrame()
{
	glUseProgram(0);
}

void URendererOpenGL::OnWindowResize(uint32 width, uint32 height)
{
	glViewport(0, 0, width, height);
}

void URendererOpenGL::DebugDrawLine(const FVector& from, const FVector& to)
{
	unsigned int VBO, VAO, CVBO;
	GLfloat points[6];

	points[0] = from.x;
	points[1] = from.y;
	points[2] = from.z;
	points[3] = to.x;
	points[4] = to.y;
	points[5] = to.z;

	GLfloat color[6];
	color[0] = 1.f;
	color[1] = 0.f;
	color[2] = 0.f;
	color[3] = 1.0f;
	color[4] = 0.0f;
	color[5] = 0.0f;

	ACamera* Camera = GetScene()->GetCamera();
	FVector cameraPos = Camera->GetLocation();

	UWindow* window = GetWindow();
	FMatrix4 projection = glm::perspective(glm::radians(45.0f), (float)window->GetWidth() / (float)window->GetHeight(), 0.001f, 10000.0f);
	FMatrix4 view = Camera->GetView();

	FMatrix4 modelMatrix = FMatrix4{ 1.f };//veresse
	glm::vec3 loc {0.0f, 0.0f, 0.0f};
	glm::vec3 sca {1.0f, 1.0f, 1.0f};
	modelMatrix = glm::translate(modelMatrix, loc);
	modelMatrix = glm::scale(modelMatrix, sca);

	Shaders["debug"]->Active();
	Shaders["debug"]->SetMatrix4("projection", projection);
	Shaders["debug"]->SetMatrix4("view", view);
	Shaders["debug"]->SetMatrix4("model", modelMatrix);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &CVBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, CVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), &color, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawArrays(GL_LINES, 0, 2);

	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &CVBO);
	glDeleteVertexArrays(1, &VAO);
	Shaders["debug"]->Deactive();
}
