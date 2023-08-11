/*********************************************************************
 *   File: Renderer.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/Renderer.hpp"
#include "Actors/Entity.hpp"

DEFAULT_BODY(BRenderer)

void BRenderer::Destroy()
{
	TMap<FString, BShader*>::iterator it;
	for (it = Shaders.begin(); it != Shaders.end(); it++)
	{
		ULOG(ELogLevel::ELL_TRACE, FText::Format("Deleting Shader %s...", it->first.c_str()));
		delete it->second;
	}
}

void BRenderer::Draw(AEntity* entity, float deltaTime)
{
	if(entity != nullptr)
		entity->Draw(deltaTime);
}

BShader* BRenderer::GetShader(const FString& shaderName)
{
	return Shaders[shaderName];
}
