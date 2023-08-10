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

void UApplication::Create()
{
	CreateWindow();
	CreateGameInstance();
	CreateRenderer();
	CreateInputManagement();
	CreatePhysicsSystem();
	CreateScene();
}

void UApplication::PostConstruct()
{
	

	GameInstance = USharedPtr<UGameInstance>::FromClass(DefaultGameInstance);
	Renderer = USharedPtr<BRenderer>::FromClass(DefaultRenderer);
	InputManagement = USharedPtr<UInputManagement>::Make();
	Scene = USharedPtr<UScene>::Make();
	PhysicsSystem = USharedPtr<UPhysicsSystem>::Make();

	Super::PostConstruct();
}

void UApplication::PostCreate()
{


	Super::PostCreate();
}

void UApplication::Initialize()
{
	//Window.Get()->Initialize();
	Window->Initialize();
	GameInstance.Get()->Initialize();
	Renderer.Get()->Initialize();
	InputManagement.Get()->Initialize();
	Scene.Get()->Initialize();
	PhysicsSystem.Get()->Initialize();

	Super::Initialize();
}

void UApplication::CreateWindow()
{
	Window = FConstructorHelper::CreateObject<UWindow>();
}
void UApplication::CreateGameInstance()
{
	GameInstance.Get()->Construct();
	GameInstance.Get()->Create();
}
void UApplication::CreateRenderer()
{
	Renderer.Get()->Construct();
	Renderer.Get()->Create();
}
void UApplication::CreateInputManagement()
{
	InputManagement.Get()->Construct();
	InputManagement.Get()->Create();
}
void UApplication::CreateScene()
{
	Scene.Get()->Construct();
	Scene.Get()->Create();
}
void UApplication::CreatePhysicsSystem()
{
	PhysicsSystem.Get()->Construct();
	PhysicsSystem.Get()->Create();
}

void UApplication::Destroy()
{
	PhysicsSystem.Destroy();
	Scene.Destroy();
	InputManagement.Destroy();
	GameInstance.Destroy();
	Renderer.Destroy();
	if(Window)
		Window->Destroy();

	delete Window;

	Super::Destroy();
}

void UApplication::Loop()
{
	float deltaTime = 0.f;
	FTime currentTime = FTime::Now();

	auto TickFunction = [](float delta)
	{
		us::env::Environment::TickComponent.Get()->Tick(delta);
	};

	//while (!Window.Get()->ShouldClose())
	while (!Window->ShouldClose())
	{
		//Window.Get()->MakeCurrent();
		//Window.Get()->StartLoop();
		Window->MakeCurrent();
		Window->StartLoop();

		//Window.Get()->PollEvents();
		Window->PollEvents();
		CalculeDeltaTime(currentTime, deltaTime);


		//Window.Get()->Update(deltaTime);
		Window->Update(deltaTime);
		GameInstance.Get()->Update(deltaTime);

		ThreadTickEvent.New(new TThread(TickFunction, deltaTime));

		OnUpdateEvent.Broadcast(deltaTime);

		ThreadTickEvent.Get()->join();

		//Window.Get()->StopLoop();
		//Window.Get()->SwapWindow();

		Window->StopLoop();
		Window->SwapWindow();
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
	Create();
	Initialize();
	Loop();
}