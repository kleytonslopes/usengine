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

#include "Core/Class.hpp"
#include <SDL.h>
#undef main
#include "glad/glad.h"

class UApplication;

class UWindow : public UClass
{
	DEFAULT_BODY(UClass);
public:
	virtual ~UWindow() final;

	// Inherited via UWeakClass
	void Initialize() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;

	void PollEvents();
	void StartLoop();
	void StopLoop();
	void SetShouldClose(bool wantClose);

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