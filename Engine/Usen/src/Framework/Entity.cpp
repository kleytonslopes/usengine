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
	Id = FGuid::NewGuid();
}

UEntity::~UEntity()
{
	if (!bIsDestroyed)
		OnDestroy();

	ULOG(ELogLevel::ELL_WARNING, FText::Format("Entity '%s' Destroyed!", Id.c_str()));
}

void UEntity::OnConstruct()
{
	AddComponent<UTransformComponent>();
	bWasConstructed = true;
}

void UEntity::Initialize()
{
	for (auto& comp : components)
	{
		comp.second->Initialize();
	}
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
	Super::OnDestroy();

	for (auto& comp : components)
	{
		delete comp.second;
	}
}

