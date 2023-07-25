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

protected:
	FString Name;
	FString VertexFilePath;
	FString FragmentFilePath;
};

#endif // !US_SHADER_HPP