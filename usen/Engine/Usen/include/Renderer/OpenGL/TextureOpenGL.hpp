/*********************************************************************
 *   File: TextureOpenGL.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_TEXTURE_OPEN_GL_HPP
#define	US_TEXTURE_OPEN_GL_HPP


#include "Renderer/Texture.hpp"
#include "TextureOpenGL-generated.hpp"

class UTextureOpenGL : public UTexture
{
	DEFAULT_BODY_GENERATED()
public:
	uint32 Id;

	explicit UTextureOpenGL();
	~UTextureOpenGL() final;
};

#endif // !US_TEXTURE_OPEN_GL_HPP