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
}

void BClass::Initialize()
{
	if (bIsInitialized)
	{
		FException::RuntimeError(FText::Format("%s Already Initialized!", GetId().c_str()));
	}

	bIsInitialized = true;

	PostInitialize();
}

void BClass::PostInitialize()
{
	bIsInitialized = true;
}

void BClass::Destroy()
{
	ULOG(ELogLevel::ELL_INFORMATION, "BClass Destroy!");

	PostDestroy();
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

UApplication* BClass::GetApplication()
{
	return Application;
}

BRenderer* BClass::GetRenderer()
{
	return Application->Renderer.Get();
}
