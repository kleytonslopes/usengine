/*********************************************************************
 *   File: Class.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Base/Class.hpp"
#include "Runtime/Application.hpp"
#include "Environment/Environment.hpp"

#include "Presentation/Window.hpp"
#include "Framework/GameInstance.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/OpenGL/RendererOpenGL.hpp"
#include "Framework/GameModeBase.hpp"
#include "Physics/PhysicsSystemPhysX.hpp"

#include "Components/UpdateComponent.hpp"


BClass::BClass() 
{
	Application = us::env::Environment::Applicaiton;

	
}

BClass::~BClass()
{
}

void BClass::Construct()
{
	entityId = GetECS()->create();

	Super::Construct();

	bCanUpdate = false;


}

void BClass::PostConstruct()
{
	Super::PostConstruct();

	//if(bCanUpdate)
	//	Application->OnUpdateEvent.Add(this, &This::Update);

	if (bCanUpdate)
	{
		TRegistryECS* ecs = GetECS();
		if (ecs)
		{
			UUpdateComponent* component = &ecs->emplace<UUpdateComponent>(entityId);
			if (component)
			{
				component->OnUpdateCalledEvent.Add(this, &This::Update);
			}
		}
	}
}


UWindow* BClass::GetWindow()
{
	return Application->Window;
}

UGameInstance* BClass::GetGameInstance()
{
	return Application->GameInstance;
}

UScene* BClass::GetScene()
{
	return Application->Scene;
}

UController* BClass::GetController()
{
	return GetGameMode()->Controller;
}

UInputManagement* BClass::GetInputManagement()
{
	return Application->InputManagement;
}

UApplication* BClass::GetApplication()
{
	return Application;
}

UGameModeBase* BClass::GetGameMode()
{
	return GetScene()->GameMode;
}

UPhysicsSystemPhysX* BClass::GetPhysicsSystemPhysX()
{
	return Application->PhysicsSystemPhysX;
}

TRegistryECS* BClass::GetECS()
{
	return &Application->ECS;
}

BRenderer* BClass::GetRenderer()
{
	return Application->Renderer;
}
