/*********************************************************************
 *   File: Shader.cpp
 *  Brief:
 *
 * Author: Kleyton
 *   Date: July 2023
 *
 * Copyright (c) 2023 Sunydark. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/Shader.hpp"

UShader::UShader(FShaderParameters& parameters)
	: Super(nullptr)
	, Name{ parameters.Name }
	, VertexFilePath{ parameters.GetVertexFilePath() }
	, FragmentFilePath{ parameters.GetFragmentFilePath() }
{

}
