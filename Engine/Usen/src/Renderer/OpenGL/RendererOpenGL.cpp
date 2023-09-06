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
}

void URendererOpenGL::PostConstruct()
{
	Super::PostConstruct();
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

	glGenFramebuffers(1, &screenFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);

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
	//glGenFramebuffers(1, &screenFBO);
	//glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);
	// create a color attachment texture

	glGenTextures(1, &screenTex);
	glBindTexture(GL_TEXTURE_2D, screenTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GetWindow()->GetWidth(), GetWindow()->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTex, 0);

	glGenRenderbuffers(1, &screenRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, screenRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, GetWindow()->GetWidth(), GetWindow()->GetHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, screenRBO);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		ULOG_Error("Invalid Framebuffer!");
	}
	/* Screen Quad */
	/* Editor */
#endif

	Super::Initialize();
}

void URendererOpenGL::StartFrame()
{
#if defined (APP_EDITOR_MODE)

	glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);
#endif

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	ACamera* Camera = GetScene()->GetCamera();

	float fov = Camera->GetFieldOfView();
	float near = Camera->GetNear();
	float far = Camera->GetFar();
	float aspect = Camera->GetAspectRatio();

	FMatrix4 projection = glm::perspective(glm::radians(fov), aspect, near, far);
	FMatrix4 view = Camera->GetView();

	TMap<FString, BShader*>::iterator shdIterator;

	for (shdIterator = Shaders.begin(); shdIterator != Shaders.end(); shdIterator++)
	{
		shdIterator->second->Active();
		shdIterator->second->SetMatrix4("projection", projection);
		shdIterator->second->SetMatrix4("view", view);
		shdIterator->second->SetMatrix4("model", FMatrix4{ 1.f });
		shdIterator->second->Deactive();
	}

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	//DrawScreenQuad();


	DebugDrawLine(FVector{ 0.f, 0.f, 0.f }, AFTransform::WorldRightVector * 100.f, FColor::Blue);
	DebugDrawLine(FVector{ 0.f, 0.f, 0.f }, AFTransform::WorldUpVector * 100.f, FColor::Green);
	DebugDrawLine(FVector{ 0.f, 0.f, 0.f }, AFTransform::WorldForwardVector * 100.f, FColor::Red);
	//
	float xPos = 0.f;
	float yPos = 0.f;
	//
	float size = 4;
	//
	for (size_t x = 0; x < size; x++)
	{
		xPos = (x + 4.f);
		DebugDrawLine(FVector{ -20.f, 0.f, xPos }, FVector{ 20.f, 0.f, xPos }, FColor::Cyan);
		DebugDrawLine(FVector{ -20.f, 0.f, -xPos }, FVector{ 20.f, 0.f, -xPos }, FColor::Cyan);
		for (size_t y = 0; y < size; y++)
		{
			yPos = (y + 4.f);
			DebugDrawLine(FVector{ yPos , 0.f, -20.f }, FVector{ yPos, 0.f, 20.f }, FColor::Pink);
			DebugDrawLine(FVector{ -yPos , 0.f, -20.f }, FVector{ -yPos, 0.f, 20.f }, FColor::Pink);
		}
	}
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

void URendererOpenGL::DebugDrawLine(const FVector& from, const FVector& to, const FColor& color)
{
	unsigned int VBO, VAO, CVBO;
	GLfloat points[6];

	points[0] = from.x;
	points[1] = from.y;
	points[2] = from.z;
	points[3] = to.x;
	points[4] = to.y;
	points[5] = to.z;

	GLfloat sColor[6];
	sColor[0] = color.R;
	sColor[1] = color.G;
	sColor[2] = color.B;
	sColor[3] = color.R;
	sColor[4] = color.G;
	sColor[5] = color.B;

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(sColor), &sColor, GL_STATIC_DRAW);
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

	//glDisable(GL_DEPTH_TEST);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Shaders["screen"]->Active();
	glBindVertexArray(screenVAO);
	glBindTexture(GL_TEXTURE_2D, screenTex);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//glBindFramebuffer(GL_FRAMEBUFFER, screenFBO);
}
