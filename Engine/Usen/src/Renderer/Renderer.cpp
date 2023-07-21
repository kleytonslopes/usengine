/*********************************************************************
 *   File: Renderer.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/Renderer.hpp"
#include "Framework/Entity.hpp"
#include "Components/RendererComponent.hpp"

URenderer::~URenderer()
{
}

void URenderer::Initialize()
{
	OnInitialized();
}

void URenderer::OnInitialized()
{
}

void URenderer::Update(float deltaTime)
{
}

void URenderer::OnDestroy()
{
}

void URenderer::Draw(UEntity* entity, float deltaTime)
{
	if (!entity)
		return;

	URendererComponent* renderComp = entity->GetComponent<URendererComponent>();
}

template<typename T>
T* URenderer::CreateShader(const FShaderParameters& parameters)
{
	T* shader = new T(parameters);
	shader->OnInitialize();

	shaders[parameters.Name] = shader;
}
