/*********************************************************************
 *   File: Class.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Base/Class.hpp"
#include "Runtime/Application.hpp"
#include "Environment.hpp"

#include "Presentation/Window.hpp"
#include "Framework/GameInstance.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/OpenGL/RendererOpenGL.hpp"


BClass::BClass() 
{
	Application = us::env::Environment::Applicaiton;
}

BClass::~BClass()
{
	ULOG(ELogLevel::ELL_WARNING, "BClass Destroyed!");
}

void BClass::Initialize()
{
	bIsInitialized = true;
}

void BClass::Destroy()
{
	ULOG(ELogLevel::ELL_INFORMATION, "BClass Destroy!");
}

UWindow* BClass::GetWindow()
{
	return Application->Window.Get();
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
	return Application->Controller.Get();
}

UInputManagement* BClass::GetInputManagement()
{
	return Application->InputManagement.Get();
}
