/*********************************************************************
 *   File: ShaderParameters.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SHADER_PARAMETERS_HPP
#define	US_SHADER_PARAMETERS_HPP

#include "Core/MinimalCore.hpp"

class FShaderParameters
{
	
public:
	FString Name{ ShaderDefault::DEFAULT };

	FString GetVertexFilePath() const
	{
		return FText::Format("../../Content/Shaders/%s/vert.glsl", Name.c_str());
	}
	FString GetFragmentFilePath() const
	{
		return FText::Format("../../Content/Shaders/%s/frag.glsl", Name.c_str());
	}
};

#endif // !US_SHADER_PARAMETERS_HPP