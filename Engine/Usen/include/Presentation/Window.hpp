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
#include <SDL.h>
#undef main
#include "glad/glad.h"
#include "Input/KeyHandler.hpp"
#include "Window-generated.hpp"

DECLARE_FUNCTION_TwoParam(FOnWindowResizedSignature, uint32, width, float, height)
DECLARE_FUNCTION_TwoParam(FOnKeyEvent, uint32, keyCode, EKeyHandler, keyHandler)

class UWindow : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	FOnWindowResizedSignature OnWindowResizedEvent;
	FOnKeyEvent OnKeyEvent;

	explicit UWindow();
	~UWindow() final;

	void Initialize() override;

	void PollEvents();
	void StartLoop();
	void StopLoop();
	void SetShouldClose(bool wantClose);
	void SwapWindow();
	void MakeCurrent();

	bool ShouldClose() const;
	uint32 GetTicks() const;

	uint32& GetWidth() { return width; }
	uint32& GetHeight() { return height; }

protected:
	void InitializeForOpenGL();

private:
	uint32 startLoop = 0;
	uint32 width = 1750;
	uint32 height = 1000;

	uint32 fpsLimit = 60;
	uint32 desiredFps = 0;
	bool bWantClose = false;

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