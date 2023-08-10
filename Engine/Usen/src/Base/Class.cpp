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
#include "Physics/PhysicsSystem.hpp"


BClass::BClass() 
{
	Application = us::env::Environment::Applicaiton;
}

BClass::~BClass()
{
}


UWindow* BClass::GetWindow()
{
	//return Application->Window.Get();
	return Application->Window;
}

UGameInstance* BClass::GetGameInstance()
{
	return Application->GameInstance.Get();
}

UScene* BClass::GetScene()
{
	return Application->Scene.Get();
}

UController* BClass::GetController()
{
	return GetGameMode()->Controller;
}

UInputManagement* BClass::GetInputManagement()
{
	return Application->InputManagement.Get();
}

UApplication* BClass::GetApplication()
{
	return Application;
}

UGameModeBase* BClass::GetGameMode()
{
	return GetScene()->GameMode.Get();
}

UPhysicsSystem* BClass::GetPhysicsSystem()
{
	return Application->PhysicsSystem.Get();
}

BRenderer* BClass::GetRenderer()
{
	return Application->Renderer.Get();
}
