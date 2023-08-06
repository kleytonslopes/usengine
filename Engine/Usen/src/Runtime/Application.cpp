/*********************************************************************
 *   File: Application.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Runtime/Application.hpp"

#include "Presentation/Window.hpp"
#include "Framework/GameInstance.hpp"
#include "Environment/Environment.hpp"
#include "Controllers/Controller.hpp"
#include "Input/InputManagement.hpp"
#include "Physics/PhysicsSystem.hpp"


UApplication::UApplication()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UApplication::~UApplication()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UApplication::Create()
{
	PostCreate();
}

void UApplication::PostCreate()
{
	CreateWindow();
	CreateGameInstance();
	CreateRenderer();
	CreateInputManagement();
	CreatePhysicsSystem();
	CreateScene();

	Initialize();
}

void UApplication::Initialize()
{
	Window.Get()->Initialize();
	GameInstance.Get()->Initialize();
	Renderer.Get()->Initialize();
	InputManagement.Get()->Initialize();
	Scene.Get()->Initialize();

	bIsInitialized = true;
	PostInitialize();
}

void UApplication::CreateWindow()
{
	Window = USharedPtr<UWindow>::Make();
	Window.Get()->Create();
}

void UApplication::CreateGameInstance()
{
	GameInstance = USharedPtr<UGameInstance>::FromClass(DefaultGameInstance);
	Window.Get()->Create();
}

void UApplication::CreateRenderer()
{
	Renderer = USharedPtr<BRenderer>::FromClass(DefaultRenderer);
}

void UApplication::CreateInputManagement()
{
	InputManagement = USharedPtr<UInputManagement>::Make();
	InputManagement.Get()->Create();
}

void UApplication::CreateScene()
{
	Scene = USharedPtr<UScene>::Make();
	Scene.Get()->Create();
}

void UApplication::CreatePhysicsSystem()
{
	PhysicsSystem = USharedPtr<UPhysicsSystem>::Make();
	PhysicsSystem.Get()->Create();
}

void UApplication::PostInitialize()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s PostInitialize!", Identity.c_str()));
}

void UApplication::Destroy()
{
	PhysicsSystem.Destroy();
	Scene.Destroy();
	InputManagement.Destroy();
	GameInstance.Destroy();
	Renderer.Destroy();
	Window.Destroy();

	PostDestroy();
}

void UApplication::PostDestroy()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s PostDestroy!", Identity.c_str()));
}

void UApplication::Loop()
{
	float deltaTime = 0.f;
	FTime currentTime = FTime::Now();

	while (!Window.Get()->ShouldClose())
	{
		Window.Get()->MakeCurrent();
		Window.Get()->StartLoop();
		
		Window.Get()->PollEvents();
		CalculeDeltaTime(currentTime, deltaTime);

		
		Window.Get()->Update(deltaTime);
		GameInstance.Get()->Update(deltaTime);
		//Scene.Get()->Update(deltaTime);
		OnUpdateEvent.Broadcast(deltaTime);

		Window.Get()->StopLoop();
		Window.Get()->SwapWindow();
	}

	Destroy();
}

void UApplication::CalculeDeltaTime(FTime& currentTime, float& deltaTime)
{
	FTime newTime = FClock::Now();
	deltaTime = FClock::Duration(newTime, currentTime);
	currentTime = newTime;
}

void UApplication::Run()
{
	Create();
	Loop();
}