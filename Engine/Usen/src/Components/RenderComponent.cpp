/*********************************************************************
 *   File: RenderComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Components/RenderComponent.hpp"

#include "Renderer/Shader.hpp"

DEFAULT_BODY(URenderComponent)

void URenderComponent::SetShader(BShader* shader)
{
	this->Shader = shader;
}

BShader* URenderComponent::GetShader()
{
	return Shader;
}
