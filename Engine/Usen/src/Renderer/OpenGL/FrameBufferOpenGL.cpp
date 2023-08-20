/*********************************************************************
 *   File: FrameBufferOpenGL.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/OpenGL/FrameBufferOpenGL.hpp"
#include <glad/glad.h>

DEFAULT_BODY(UFrameBufferOpenGL)

void UFrameBufferOpenGL::Construct()
{
	Super::Construct();


}

void UFrameBufferOpenGL::Destroy()
{
	Super::Destroy();

	glDeleteFramebuffers(1, &FBO);
}

void UFrameBufferOpenGL::Initialize()
{
	Super::Initialize();
	Invalidate();
}

void UFrameBufferOpenGL::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void UFrameBufferOpenGL::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void UFrameBufferOpenGL::DrawScreenQuad()
{

}

uint32 UFrameBufferOpenGL::GetColorAttachment() const
{
	return FrameTexture;
}

void UFrameBufferOpenGL::Invalidate()
{
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glGenTextures(1, &FrameTexture);
	glBindTexture(GL_TEXTURE_2D, FrameTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FrameTexture, 0);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		ULOG_Error("Invalid Framebuffer!");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	/*
	if (RendererId)
	{
		glDeleteFramebuffers(1, &RendererId);
		glDeleteTextures(1, &DepthAttachment);
	}
	glGenFramebuffers(1, &RendererId);
	glBindFramebuffer(GL_FRAMEBUFFER, RendererId);

	glGenTextures(1, &ColorAttachment);
	glBindTexture(GL_TEXTURE_2D, ColorAttachment);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Settings.Width, Settings.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorAttachment, 0);
	glGenTextures(1, &DepthAttachment);
	glBindTexture(GL_TEXTURE_2D, DepthAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, Settings.Width, Settings.Height);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, DepthAttachment, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		FException::RuntimeError("Invalid Framebuffer!");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	*/

}
