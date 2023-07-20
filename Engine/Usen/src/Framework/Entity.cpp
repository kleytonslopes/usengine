/*********************************************************************
 *   File: Entity.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Framework/Entity.hpp"

#include "Components/Interface/IComponent.hpp"
#include "Framework/Scene.hpp"
#include "Core/Guid.hpp"

#include "Components/TransformComponent.hpp"

UEntity::UEntity(UScene* scene) : scene{ scene }
{
	id = FGuid::NewGuid();
}

void UEntity::Initialize()
{

}

void UEntity::Update(float deltaTime)
{
	for (auto& comp : components)
	{
		if (comp.second->CanTick())
			comp.second->Update(deltaTime);
	}
}

void UEntity::OnDestroy()
{

}

void UEntity::OnConstruct()
{
	AddComponent<UTransformComponent>();
}
