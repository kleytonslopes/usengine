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
	void Initialize() override;
	void StartFrame() override;
	void EndFrame() override;
	void OnWindowResize(uint32 width, uint32 height) override;
};

#endif // !US_RENDERER_OPEN_GL_HPP