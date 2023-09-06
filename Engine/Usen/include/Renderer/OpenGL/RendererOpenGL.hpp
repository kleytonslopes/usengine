/*********************************************************************
 *   File: RendererOpenGL.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_RENDERER_OPEN_GL_HPP
#define	US_RENDERER_OPEN_GL_HPP


#include "Renderer/Renderer.hpp"
#include "RendererOpenGL-generated.hpp"

class URendererOpenGL : public BRenderer
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	void PostConstruct() override;
	void Destroy() override;

	void Initialize() override;
	void StartFrame() override;
	void EndFrame() override;
	void OnWindowResize(uint32 width, uint32 height) override;
	void OnViewportResize(uint32 width, uint32 height) override;
	void DebugDrawLine(const FVector& from, const FVector& to, const FColor& color) override;
	void DrawScreenQuad() override;

	uint32 GetScreenTex() { return screenTex; }

private:
	uint32 screenVAO;
	uint32 screenVBO;
	uint32 screenFBO;
	uint32 screenRBO;
	uint32 screenTex;

};

#endif // !US_RENDERER_OPEN_GL_HPP