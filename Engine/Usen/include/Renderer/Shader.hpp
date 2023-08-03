/*********************************************************************
 *   File: Shader.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SHADER_HPP
#define	US_SHADER_HPP


#include "Base/Class.hpp"
#include "Shader-generated.hpp"

class BShader : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit BShader();
	virtual ~BShader();

	virtual void LoadShader(UCharPtr vertexShaderFile, UCharPtr fragmentShaderFileName) = 0;

	virtual void Active() = 0;
	virtual void Deactive() = 0;

	virtual void SetBool(const FString& name, bool value) = 0;
	virtual void SetInt(const FString& name, int value) = 0;
	virtual void SetFloat(const FString& name, float value) = 0;
	virtual void SetVector2(const FString& name, FVector2 value) = 0;
	virtual void SetVector2(const FString& name, float x, float y) = 0;
	virtual void SetVector3(const FString& name, FVector value) = 0;
	virtual void SetVector3(const FString& name, float x, float y, float z) = 0;
	virtual void SetVector4(const FString& name, FVector4 value) = 0;
	virtual void SetVector4(const FString& name, float x, float y, float z, float w) = 0;

	virtual void SetMatrix2(const FString& name, FMatrix2 value)= 0;
	virtual void SetMatrix3(const FString& name, FMatrix3 value)= 0;
	virtual void SetMatrix4(const FString& name, FMatrix4 value)= 0;
protected:
	FString Name;
	FString VertexFilePath;
	FString FragmentFilePath;
};

#endif // !US_SHADER_HPP