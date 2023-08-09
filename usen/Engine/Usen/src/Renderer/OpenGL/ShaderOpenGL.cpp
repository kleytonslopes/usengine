/*********************************************************************
 *   File: ShaderOpenGL.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/OpenGL/ShaderOpenGL.hpp"

UShaderOpenGL::UShaderOpenGL()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UShaderOpenGL::~UShaderOpenGL()
{
	glDeleteProgram(programId);
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UShaderOpenGL::LoadShader(UCharPtr vertexShaderFile, UCharPtr fragmentShaderFileName)
{
	vertId = LoadShader(vertexShaderFile, GL_VERTEX_SHADER);
	fragId = LoadShader(fragmentShaderFileName, GL_FRAGMENT_SHADER);

	CreateProgram();

	glDetachShader(programId, vertId);
	glDetachShader(programId, fragId);

	glDeleteShader(vertId);
	glDeleteShader(fragId);
}

void UShaderOpenGL::Active()
{
	glUseProgram(programId);
}

void UShaderOpenGL::Deactive()
{
	glUseProgram(0);
}

void UShaderOpenGL::SetBool(const FString& name, bool value)
{
	glUniform1i(glGetUniformLocation(programId, name.c_str()), (int)value);
}

void UShaderOpenGL::SetInt(const FString& name, int value)
{
	glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void UShaderOpenGL::SetFloat(const FString& name, float value)
{
	glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}

void UShaderOpenGL::SetVector2(const FString& name, FVector2 value)
{
	glUniform2fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
}

void UShaderOpenGL::SetVector2(const FString& name, float x, float y)
{
	glUniform2f(glGetUniformLocation(programId, name.c_str()), x, y);
}

void UShaderOpenGL::SetVector3(const FString& name, FVector value)
{
	glUniform3fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
}

void UShaderOpenGL::SetVector3(const FString& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(programId, name.c_str()), x, y, z);
}

void UShaderOpenGL::SetVector4(const FString& name, FVector4 value)
{
	glUniform4fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
}

void UShaderOpenGL::SetVector4(const FString& name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(programId, name.c_str()), x, y, z, w);
}

void UShaderOpenGL::SetMatrix2(const FString& name, FMatrix2 value)
{
	glUniformMatrix2fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void UShaderOpenGL::SetMatrix3(const FString& name, FMatrix3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void UShaderOpenGL::SetMatrix4(const FString& name, FMatrix4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

GLuint UShaderOpenGL::LoadShader(UCharPtr fileName, int shaderType)
{
	FString shaderSrc = FFile::Read(fileName);

	assert(!shaderSrc.empty());
	UCharPtr shaderSrcPtr = shaderSrc.c_str();

	GLuint shaderId = glCreateShader(shaderType);

	glShaderSource(shaderId, 1, &shaderSrcPtr, nullptr);
	glCompileShader(shaderId);

	CheckShader(shaderId);

	return shaderId;
}

void UShaderOpenGL::CheckShader(GLuint shaderId)
{
	GLint result = GL_TRUE;

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		GLint logLen = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0)
		{
			FString shaderInfLog(logLen, '\0');
			glGetShaderInfoLog(shaderId, logLen, nullptr, &shaderInfLog[0]);
			FLogger::Error("shader has error: ");
			FLogger::Error(shaderInfLog);

			assert(false);
		}
	}
}

void UShaderOpenGL::CreateProgram()
{
	programId = glCreateProgram();
	glAttachShader(programId, vertId);
	glAttachShader(programId, fragId);
	glLinkProgram(programId);

	GLint result = GL_TRUE;
	glGetProgramiv(programId, GL_LINK_STATUS, &result);

	if (result == GL_FALSE)
	{
		ULOG(ELogLevel::ELL_ERROR, "Failed to Link Program");
		assert(false);
	}
}
