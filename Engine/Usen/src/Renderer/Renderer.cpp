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

BRenderer::BRenderer()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

BRenderer::~BRenderer()
{
	TMap<FString, BShader*>::iterator it;
	for (it = Shaders.begin(); it != Shaders.end(); it++)
	{
		ULOG(ELogLevel::ELL_TRACE, FText::Format("Deleting Shader %s...", it->first.c_str()));
		delete it->second;
	}

	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void BRenderer::Draw(AEntity* entity, float deltaTime)
{
	if(entity != nullptr)
		entity->Draw(deltaTime);
}


template<typename T>
inline T* BRenderer::CreateShader(const FShaderParameters& parameters)
{
	T* shader = new T(parameters);
	shader->Initialize();

	shaders[parameters.Name] = shader;
}