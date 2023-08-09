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
	virtual void LoadShader(UCharPtr vertexShaderFile, UCharPtr fragmentShaderFileName) { /* override */ };

	virtual void Active() { /* override */ };
	virtual void Deactive() { /* override */ };

	virtual void SetBool(const FString& name, bool value) { /* override */ };
	virtual void SetInt(const FString& name, int value) { /* override */ };
	virtual void SetFloat(const FString& name, float value) { /* override */ };
	virtual void SetVector2(const FString& name, FVector2 value) { /* override */ };
	virtual void SetVector2(const FString& name, float x, float y) { /* override */ };
	virtual void SetVector3(const FString& name, FVector value) { /* override */ };
	virtual void SetVector3(const FString& name, float x, float y, float z) { /* override */ };
	virtual void SetVector4(const FString& name, FVector4 value) { /* override */ };
	virtual void SetVector4(const FString& name, float x, float y, float z, float w) { /* override */ };

	virtual void SetMatrix2(const FString& name, FMatrix2 value) { /* override */ };
	virtual void SetMatrix3(const FString& name, FMatrix3 value) { /* override */ };
	virtual void SetMatrix4(const FString& name, FMatrix4 value) { /* override */ };
protected:
	FString Name;
	FString VertexFilePath;
	FString FragmentFilePath;
};

#endif // !US_SHADER_HPP