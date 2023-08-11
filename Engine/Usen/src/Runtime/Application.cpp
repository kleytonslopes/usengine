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

DEFAULT_BODY(UApplication);

////void UApplication::Create()
////{
////	CreateWindow();
////	CreateGameInstance();
////	CreateRenderer();
////	CreateInputManagement();
////	CreatePhysicsSystem();
////	CreateScene();
////}

void UApplication::PostConstruct()
{
	Super::PostConstruct();

	Window = FConstructorHelper::CreateObject<UWindow>();
	GameInstance = FConstructorHelper::CreateObject<UGameInstance>();
	Renderer = FConstructorHelper::CreateObject<URendererOpenGL>();
	InputManagement = FConstructorHelper::CreateObject<UInputManagement>();
	Scene = FConstructorHelper::CreateObject<UScene>();
	PhysicsSystem = FConstructorHelper::CreateObject<UPhysicsSystem>();
}

void UApplication::Initialize()
{
	Window->Initialize();
	GameInstance->Initialize();
	Renderer->Initialize();
	InputManagement->Initialize();
	Scene->Initialize();
	PhysicsSystem->Initialize();

	Super::Initialize();
}

void UApplication::Destroy()
{
	//if (PhysicsSystem) PhysicsSystem->Destroy();
	//if (Scene) Scene->Destroy();
	//if (InputManagement) InputManagement->Destroy();
	//if (GameInstance) GameInstance->Destroy();
	//if (Renderer) Renderer->Destroy();
	//if (Window) Window->Destroy();

	delete PhysicsSystem;	PhysicsSystem = nullptr;
	delete Scene;           Scene = nullptr;
	delete InputManagement; InputManagement = nullptr;
	delete GameInstance;    GameInstance = nullptr;
	delete Renderer;        Renderer = nullptr;
	delete Window;          Window = nullptr;

	Super::Destroy();
}

void UApplication::Loop()
{
	float deltaTime = 0.f;
	FTime currentTime = FTime::Now();

	auto TickFunction = [](float delta)
	{
		us::env::Environment::TickComponent->Tick(delta);
	};

	//while (!Window->ShouldClose())
	while (!Window->ShouldClose())
	{
		Window->MakeCurrent();
		Window->StartLoop();

		Window->PollEvents();
		CalculeDeltaTime(currentTime, deltaTime);


		Window->Update(deltaTime);
		GameInstance->Update(deltaTime);

		ThreadTickEvent = new TThread(TickFunction, deltaTime);

		OnUpdateEvent.Broadcast(deltaTime);

		ThreadTickEvent->join();

		Window->StopLoop();
		Window->SwapWindow();

		delete ThreadTickEvent;
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
	Construct();
	PostConstruct();

	Initialize();
	PostInitialize();

	Loop();
}