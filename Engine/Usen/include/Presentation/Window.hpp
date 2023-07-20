/*********************************************************************
 *   File: Window.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_WINDOW_HPP
#define	US_WINDOW_HPP

#include "Core/WeakClass.hpp"
#include <SDL.h>
#undef main

class UApplication;

class UWindow : public UWeakClass
{
public:
	UWindow(UApplication* application);
	virtual ~UWindow();

	void Initialize() override;

	void Update(float deltaTime) override;

	void PollEvents();
	void StartLoop();
	void StopLoop();
	void SetShouldClose(bool wantClose);

	bool ShouldClose() const;
	uint32 GetTicks() const;

protected:
	void InitializeForOpenGL();

private:
	UApplication* application;
	uint32 startLoop = 0;

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