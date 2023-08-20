/*********************************************************************
 *   File: FrameBufferOpenGL.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_FRAME_BUFFER_OPEN_GL_HPP
#define	US_FRAME_BUFFER_OPEN_GL_HPP


#include "Renderer/FrameBuffer.hpp"
#include "FrameBufferOpenGL-generated.hpp"

class UFrameBufferOpenGL : public UFrameBuffer
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	void Destroy() override;

	void Initialize() override;

	void Bind() override;
	void Unbind() override;

	void DrawScreenQuad() override;

	uint32 GetColorAttachment() const override;
private:
	uint32 FBO;
	uint32 RBO;
	uint32 FrameTexture;
	uint32 DepthAttachment;

	void Invalidate();
};

#endif // !US_FRAME_BUFFER_OPEN_GL_HPP