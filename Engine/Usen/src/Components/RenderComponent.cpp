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

URenderComponent::URenderComponent()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

URenderComponent::~URenderComponent()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void URenderComponent::SetShader(BShader* shader)
{
	this->Shader = shader;
}
