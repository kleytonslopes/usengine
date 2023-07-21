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
	FString Name{"default"};
	FString VertexFilePath;
	FString FragmentFilePath;
};

#endif // !US_SHADER_PARAMETERS_HPP
