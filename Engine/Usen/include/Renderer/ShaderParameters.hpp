/*********************************************************************
 *   File: ShaderParameters.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SHADER_PARAMETERS_HPP
#define	US_SHADER_PARAMETERS_HPP

#include "Core/String.hpp"

struct FShaderParameters
{
	FString Name{ ShaderDefault::DEFAULT };

	FString GetVertexFilePath()
	{
		return FText::Format("../../Content/Shaders/%s/vert.glsl", Name.c_str());
	}
	FString GetFragmentFilePath()
	{
		return FText::Format("../../Content/Shaders/%s/frag.glsl", Name.c_str());
	}
};

#endif // !US_SHADER_PARAMETERS_HPP
