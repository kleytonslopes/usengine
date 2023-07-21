/*********************************************************************
 *   File: ShaderOpenGL.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SHADER_OPENGL_HPP
#define	US_SHADER_OPENGL_HPP

#include "Renderer/Shader.hpp"
#include <glad/glad.h>

class UShaderOpenGL : public UShader
{
	DEFAULT_BODY(UShader);
public:
	virtual void Initialize() override;
	virtual void OnInitialized() override;
	virtual void OnDestroy() override;

	void Active();
	void Deactivate();

protected:
	GLuint vertId;
	GLuint fragId;
	GLuint programId;
};

#endif // !US_SHADER_OPENGL_HPP