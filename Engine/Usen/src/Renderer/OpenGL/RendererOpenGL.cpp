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
#include "Renderer/OpenGL/FrameBufferOpenGL.hpp"

#include "Framework/GameInstance.hpp"
#include "Framework/Scene.hpp"
#include "Camera/Camera.hpp"

#include <glad/glad.h>

#include "Presentation/Window.hpp"

DEFAULT_BODY(URendererOpenGL)

void URendererOpenGL::Construct()
{
	Super::Construct();

	//FrameBuffer = FConstructorHelper::CreateObject<UFrameBufferOpenGL>();
}

void URendererOpenGL::PostConstruct()
{
	Super::PostConstruct();

	//FFrameBufferSettings FrameBufferSettings{};
	//FrameBufferSettings.Width = GetWindow()->GetWidth();
	//FrameBufferSettings.Height = GetWindow()->GetHeight();
	//
	//FrameBuffer->SetFrameBufferSettings(FrameBufferSettings);


}

void URendererOpenGL::Destroy()
{
	Super::Destroy();
	glDeleteVertexArrays(1, &screenVAO);
	glDeleteBuffers(1, &screenVBO);
	glDeleteFramebuffers(1, &screenFBO);
}

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

#if defined (APP_EDITOR_MODE)
	/* Editor */
	/* Screen Quad */
	float screenVertices[] = {
		// vertices   // uv
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &screenVAO);
	glGenBuffers(1, &screenVBO);
	glBindVertexArray(screenVAO);
	glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), &screenVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	// framebuffer configuration
	glGenFramebuffers(1, &screenFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);
	// create a color attachment texture
	
	glGenTextures(1, &screenTex);
	glBindTexture(GL_TEXTURE_2D, screenTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GetWindow()->GetWidth(), GetWindow()->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTex, 0);
	/* Screen Quad */
	/* Editor */
#endif

	Super::Initialize();
}

void URendererOpenGL::StartFrame()
{
#if defined (APP_EDITOR_MODE)
	glBindFramebuffer(GL_FRAMEBUFFER, screenVBO);
#endif

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	/*glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);*/
	
	ACamera* Camera = GetScene()->GetCamera();
	FVector cameraPos = Camera->GetLocation();

	float fov = Camera->GetFieldOfView();
	float near = Camera->GetNear();
	float far = Camera->GetFar();
	float aspect = Camera->GetAspectRatio();

	UWindow* window = GetWindow();
	FMatrix4 projection = glm::perspective(glm::radians(fov), aspect, near, far);
	FMatrix4 view = Camera->GetView();

	FMatrix4 modelMatrix = FMatrix4{ 1.f };//veresse

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

	//glEnable(GL_DEPTH_TEST);
}

void URendererOpenGL::EndFrame()
{
	glUseProgram(0);
}

void URendererOpenGL::OnWindowResize(uint32 width, uint32 height)
{
	glViewport(0, 0, width, height);
}

void URendererOpenGL::OnViewportResize(uint32 width, uint32 height)
{
	glDeleteVertexArrays(1, &screenVAO);
	glDeleteBuffers(1, &screenVBO);
	glDeleteFramebuffers(1, &screenFBO);

	/* Screen Quad */
	float screenVertices[] = {
		// vertices   // uv
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &screenVAO);
	glGenBuffers(1, &screenVBO);
	glBindVertexArray(screenVAO);
	glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), &screenVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	// framebuffer configuration
	glGenFramebuffers(1, &screenFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);
	// create a color attachment texture

	glGenTextures(1, &screenTex);
	glBindTexture(GL_TEXTURE_2D, screenTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GetWindow()->GetWidth(), GetWindow()->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTex, 0);
	/* Screen Quad */

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

void URendererOpenGL::DrawScreenQuad()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Shaders["screen"]->Active();
	glBindVertexArray(screenVAO);
	glBindTexture(GL_TEXTURE_2D, screenTex);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
