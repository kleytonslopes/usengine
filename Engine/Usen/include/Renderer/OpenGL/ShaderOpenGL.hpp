/*********************************************************************
 *   File: ShaderOpenGL.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SHADER_OPEN_GL_HPP
#define	US_SHADER_OPEN_GL_HPP


#include "Renderer/Shader.hpp"
#include <glad/glad.h>
#include "ShaderOpenGL-generated.hpp"

class UShaderOpenGL : public BShader
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UShaderOpenGL();
	~UShaderOpenGL() final;

	void LoadShader(UCharPtr vertexShaderFile, UCharPtr fragmentShaderFileName) override;

	void Active();
	void Deactive();

	void SetBool(const FString& name, bool value);
	void SetInt(const FString& name, int value);
	void SetFloat(const FString& name, float value);
	void SetVector2(const FString& name, FVector2 value);
	void SetVector2(const FString& name, float x, float y);
	void SetVector3(const FString& name, FVector value);
	void SetVector3(const FString& name, float x, float y, float z);
	void SetVector4(const FString& name, FVector4 value);
	void SetVector4(const FString& name, float x, float y, float z, float w);

	void SetMatrix2(const FString& name, FMatrix2 value);
	void SetMatrix3(const FString& name, FMatrix3 value);
	void SetMatrix4(const FString& name, FMatrix4 value);

private:
	GLuint vertId;
	GLuint fragId;
	GLuint programId;

	GLuint LoadShader(UCharPtr fileName, int shaderType);

	void CheckShader(GLuint shaderId);
	void CreateProgram();
};

#endif // !US_SHADER_OPEN_GL_HPP