/*********************************************************************
 *   File: RendererOpenGL.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_RENDERER_OPENGL_HPP
#define	US_RENDERER_OPENGL_HPP

#include "Renderer/Renderer.hpp"

class UShader;
class UEntity;

class URendererOpenGL : public URenderer
{
	DEFAULT_BODY(URenderer);
public:
	virtual ~URendererOpenGL();

	void Initialize() override;
};

#endif // !US_RENDERER_HPP