/*********************************************************************
 *   File: RendererOpenGL.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
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
	explicit URendererOpenGL();
	virtual ~URendererOpenGL();

	void Initialize() override;
};

#endif // !US_RENDERER_OPEN_GL_HPP