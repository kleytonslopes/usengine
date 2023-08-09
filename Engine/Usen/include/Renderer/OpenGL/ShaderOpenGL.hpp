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
	void LoadShader(UCharPtr vertexShaderFile, UCharPtr fragmentShaderFileName) override;
	void Destroy() override;

	void Active() override;
	void Deactive() override;

	void SetBool(const FString& name, bool value) override;
	void SetInt(const FString& name, int value) override;
	void SetFloat(const FString& name, float value) override;
	void SetVector2(const FString& name, FVector2 value) override;
	void SetVector2(const FString& name, float x, float y) override;
	void SetVector3(const FString& name, FVector value) override;
	void SetVector3(const FString& name, float x, float y, float z) override;
	void SetVector4(const FString& name, FVector4 value) override;
	void SetVector4(const FString& name, float x, float y, float z, float w) override;

	void SetMatrix2(const FString& name, FMatrix2 value) override;
	void SetMatrix3(const FString& name, FMatrix3 value) override;
	void SetMatrix4(const FString& name, FMatrix4 value) override;

	GLuint GetProgramId() const { return programId; }
private:
	GLuint vertId;
	GLuint fragId;
	GLuint programId;

	GLuint LoadShader(UCharPtr fileName, int shaderType);

	void CheckShader(GLuint shaderId);
	void CreateProgram();
};

#endif // !US_SHADER_OPEN_GL_HPP