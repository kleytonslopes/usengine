/*********************************************************************
 *   File: Window.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: July 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef US_WINDOW_HPP
#define	US_WINDOW_HPP


#include "Base/Class.hpp"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include <SDL.h>
#undef main
#include "glad/glad.h"
#include "Input/KeyHandler.hpp"
#include "Window-generated.hpp"

DECLARE_FUNCTION_OneParam(FOnPollEventsSignature, SDL_Event*, sEvent)
DECLARE_FUNCTION_TwoParam(FOnWindowResizedSignature, uint32, width, uint32, height)
DECLARE_FUNCTION_TwoParam(FOnKeyEvent, uint32, keyCode, EKeyHandler, keyHandler)
DECLARE_FUNCTION_TwoParam(FOnMouseButtonEvent, uint32, keyCode, EKeyHandler, keyHandler)
DECLARE_FUNCTION_TwoParam(FOnMouseWheelEvent, uint32, xOffset, uint32, yOffset)

DECLARE_FUNCTION_FourParam(FOnMouseMovementEvent, uint32, xPos, uint32, yPos, uint32, xPosRel, uint32, yPosRel)

class UWindow : public BClass
{
	DEFAULT_BODY_GENERATED()

public:
	FOnPollEventsSignature OnPollEventsEvent;
	FOnWindowResizedSignature OnWindowResizedEvent;
	FOnKeyEvent OnKeyEvent;
	FOnMouseButtonEvent OnMouseButtonEvent;
	FOnMouseWheelEvent OnMouseWheelEvent;
	FOnMouseMovementEvent OnMouseMovementEvent;

	void Construct() override;
	void PostConstruct() override;
	void Destroy() override;

	void Initialize() override;

	void PollEvents();
	void StartLoop();
	void StopLoop();
	void SetShouldClose(bool wantClose);
	void SwapWindow();
	void MakeCurrent();
	void SetMouseLocked(bool mouseLock);

	bool ShouldClose() const;
	bool IsMouseLocked() const;
	uint32 GetTicks() const;

	uint32& GetWidth() { return width; }
	uint32& GetHeight() { return height; }
	SDL_Window* GetSDLWIndow() { return sdlWindow; }
	SDL_GLContext* GetSDLContext() { return &sdlGLContext; }

protected:
	void InitializeForOpenGL();

private:
	uint32 startLoop = 0;
	uint32 width = 1750;
	uint32 height = 1000;

	uint32 fpsLimit = 60;
	uint32 desiredFps = 0;
	bool bWantClose = false;
	bool bIsMouseLocked = false;

	SDL_Event sdlEvent;
	SDL_Window* sdlWindow = nullptr;
	SDL_Surface* sdlSurface = nullptr;
	SDL_Renderer* sdlRenderer = nullptr;
	SDL_GLContext sdlGLContext;

	void CreateWindowInstance(FString title, uint32 width, uint32 height, int contextFlags);
	void CreateWindowRendererInstance();
	void CreateWindowSurfaceInstance();
	void CreateWindowContextOpenGL();
};

#endif // !US_WINDOW_HPP