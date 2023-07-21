/*********************************************************************
 *   File: Shader.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SHADER_HPP
#define	US_SHADER_HPP

#include "Core/Class.hpp"
#include "Renderer/ShaderParameters.hpp"

class UShader : public UClass
{
	DEFAULT_BODY(UClass);
public:
	explicit UShader(FShaderParameters& parameters);

protected:
	FString Name;
	FString VertexFilePath;
	FString FragmentFilePath;
};

#endif // !US_SHADER_HPP