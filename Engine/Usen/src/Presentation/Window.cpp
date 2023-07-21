/*********************************************************************
 *   File: Window.cpp
 *  Brief:
 *
 * Author: Kleyton
 *   Date: July 2023
 *
 * Copyright (c) 2023 Sunydark. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Presentation/Window.hpp"
#include "Runtime/Application.hpp"

UWindow::~UWindow()
{
	if (!bIsDestroyed)
		OnDestroy();
}

void UWindow::Initialize()
{
	ULOG(ELogLevel::ELL_TRACE, "Initializing Window...");

	desiredFps = 1000 / fpsLimit;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		UASSERT(false, "Failed to Initialize window!");
	}

	InitializeForOpenGL();
}

void UWindow::Update(float deltaTime)
{

}

void UWindow::PollEvents()
{
	while (SDL_PollEvent(&sdlEvent) != 0)
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			SetShouldClose(true);
			break;
		default:

			break;
		}
	}
}

void UWindow::StartLoop()
{
	startLoop = GetTicks();
}

void UWindow::StopLoop()
{
	uint32 delta = GetTicks() - startLoop;
	if (delta < desiredFps)
	{
		SDL_Delay(desiredFps - delta);
	}
}

void UWindow::SetShouldClose(bool wantClose)
{
	bWantClose = wantClose;
}

bool UWindow::ShouldClose() const
{
	return bWantClose;
}

uint32 UWindow::GetTicks() const
{
	return SDL_GetTicks();
}

void UWindow::InitializeForOpenGL()
{
	uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	int context_flags = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
#ifdef _DEBUG
	context_flags |= SDL_GL_CONTEXT_DEBUG_FLAG;
#endif // DEBUG

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, context_flags);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	CreateWindowInstance("USen", width, height, windowFlags);
	CreateWindowRendererInstance();
	CreateWindowSurfaceInstance();
	CreateWindowContextOpenGL();
}

void UWindow::CreateWindowInstance(FString title, uint32 width, uint32 height, int contextFlags)
{
	sdlWindow = SDL_CreateWindow(title.c_str()
		, SDL_WINDOWPOS_CENTERED
		, SDL_WINDOWPOS_CENTERED
		, width
		, height
		, contextFlags);
}

void UWindow::CreateWindowRendererInstance()
{
	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
	SDL_RenderClear(sdlRenderer);
	SDL_RenderPresent(sdlRenderer);
}

void UWindow::CreateWindowSurfaceInstance()
{
	sdlSurface = SDL_GetWindowSurface(sdlWindow);
	SDL_FillRect(sdlSurface, NULL, SDL_MapRGB(sdlSurface->format, 0x00, 0x00, 0x00));
	SDL_UpdateWindowSurface(sdlWindow);

}

void UWindow::CreateWindowContextOpenGL()
{
	sdlGLContext = SDL_GL_CreateContext(sdlWindow);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		UASSERT(false, "Failed to initialize GLAD");
	}
}

void UWindow::OnDestroy()
{
	Super::OnDestroy();

	if (sdlGLContext)
		SDL_GL_DeleteContext(sdlGLContext);

	SDL_FreeSurface(sdlSurface);
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
	ULOG(ELogLevel::ELL_WARNING, "UWindow Destroyed!");
}
