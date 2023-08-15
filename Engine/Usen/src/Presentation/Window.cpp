/*********************************************************************
 *   File: Window.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: July 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Presentation/Window.hpp"
#include "Runtime/Application.hpp"

DEFAULT_BODY(UWindow)

void UWindow::Construct()
{
	desiredFps = 1000 / fpsLimit;

	Super::Construct();
}

void UWindow::PostConstruct()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		UASSERT(false, "Failed to Initialize window!");
	}

	Super::PostConstruct();
}

void UWindow::Destroy()
{
	if (sdlGLContext)
		SDL_GL_DeleteContext(sdlGLContext);

	SDL_FreeSurface(sdlSurface);
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}

void UWindow::Initialize()
{
	InitializeForOpenGL();

	Super::Initialize();
}

void UWindow::PollEvents()
{
	while (SDL_PollEvent(&sdlEvent) != 0)
	{
		switch (sdlEvent.type)
		{
		case SDL_MOUSEMOTION:
			OnMouseMovementEvent.Broadcast(sdlEvent.motion.x, sdlEvent.motion.y, sdlEvent.motion.xrel, sdlEvent.motion.yrel);
			break;
		case SDL_KEYDOWN:
			OnKeyEvent.Broadcast(sdlEvent.key.keysym.sym, EKeyHandler::KEY_PRESSED);
			break;
		case SDL_KEYUP:
			OnKeyEvent.Broadcast(sdlEvent.key.keysym.sym, EKeyHandler::KEY_RELEASED);
			break;
		case SDL_MOUSEBUTTONDOWN:
			OnMouseButtonEvent.Broadcast(sdlEvent.button.button, EKeyHandler::KEY_PRESSED);
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonEvent.Broadcast(sdlEvent.button.button, EKeyHandler::KEY_RELEASED);
			break;
		case SDL_MOUSEWHEEL:
			OnMouseWheelEvent.Broadcast(sdlEvent.wheel.x, sdlEvent.wheel.y);
			break;
		case SDL_QUIT:
			SetShouldClose(true);
			break;
		case SDL_WINDOWEVENT:
			if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				OnWindowResizedEvent.Broadcast(sdlEvent.window.data1, sdlEvent.window.data2);
			}
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

void UWindow::SwapWindow()
{
	SDL_GL_SwapWindow(sdlWindow);
}

void UWindow::MakeCurrent()
{
	SDL_GL_MakeCurrent(sdlWindow, sdlGLContext);
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
	int displays = SDL_GetNumVideoDisplays();

	TVector<SDL_Rect> displayBounds;
	for (int i = 0; i < displays; i++) {
		displayBounds.push_back(SDL_Rect());
		SDL_GetDisplayBounds(i, &displayBounds.back());
	}

	int x = displayBounds[1].x + 50;
	int y = displayBounds[1].y + 50;
	int w = width;
	int h = height;

	sdlWindow = SDL_CreateWindow(title.c_str()
		, x
		, y
		, w
		, h
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
