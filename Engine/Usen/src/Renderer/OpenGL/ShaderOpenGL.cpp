/*********************************************************************
 *   File: ShaderOpenGL.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/OpenGL/ShaderOpenGL.hpp"


void UShaderOpenGL::Initialize()
{

}

void UShaderOpenGL::OnInitialized()
{

}

void UShaderOpenGL::OnDestroy()
{
	glDeleteProgram(programId);
}

void UShaderOpenGL::Active()
{
	glUseProgram(programId);
}

void UShaderOpenGL::Deactivate()
{
	glUseProgram(0);
}
