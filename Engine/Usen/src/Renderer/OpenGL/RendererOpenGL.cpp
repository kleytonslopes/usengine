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
		shdIterator->second->Deactive();
	}

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
}

void URendererOpenGL::EndFrame()
{
	glUseProgram(0);
}

void URendererOpenGL::OnWindowResize(uint32 width, uint32 height)
{
	glViewport(0, 0, width, height);
}
