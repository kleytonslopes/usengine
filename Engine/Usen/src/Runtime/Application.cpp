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
#include "Physics/PhysicsSystemPhysX.hpp"

#include "Components/UpdateComponent.hpp"

DEFAULT_BODY(UApplication);

void UApplication::PostConstruct()
{
	Super::PostConstruct();

	Window = FConstructorHelper::CreateObject<UWindow>();
	Window->Initialize();
	GameInstance = FConstructorHelper::CreateObject<UGameInstance>();
	Renderer = FConstructorHelper::CreateObject<URendererOpenGL>();
	Renderer->Initialize();
	InputManagement = FConstructorHelper::CreateObject<UInputManagement>();
	PhysicsSystem = FConstructorHelper::CreateObject<UPhysicsSystem>();
	PhysicsSystemPhysX = FConstructorHelper::CreateObject<UPhysicsSystemPhysX>();
	Scene = FConstructorHelper::CreateObject<UScene>();
}

void UApplication::Initialize()
{
	/*Window->Initialize();*/
	GameInstance->Initialize();
	/*Renderer->Initialize();*/
	InputManagement->Initialize();
	Scene->Initialize();
	PhysicsSystem->Initialize();
	PhysicsSystemPhysX->Initialize();

	Super::Initialize();
}

void UApplication::Destroy()
{
	delete PhysicsSystemPhysX; PhysicsSystemPhysX = nullptr;
	delete PhysicsSystem;	   PhysicsSystem = nullptr;
	delete Scene;              Scene = nullptr;
	delete InputManagement;    InputManagement = nullptr;
	delete GameInstance;       GameInstance = nullptr;
	delete Renderer;           Renderer = nullptr;
	delete Window;             Window = nullptr;

	Super::Destroy();
}

void UApplication::Draw(float deltaTime)
{
	PhysicsSystemPhysX->Update(deltaTime);

	Renderer->StartFrame(0, 0, Window->GetWidth(), Window->GetHeight(), true);
#if defined (APP_EDITOR_MODE)
	DrawScreenQuad();
#endif
		OnDrawEvent.Broadcast(deltaTime);
		//PhysicsSystem->Update(deltaTime);
		/*PhysicsSystemPhysX->Update(deltaTime);*/
	//Renderer->EndFrame();

	Renderer->StartFrame(Window->GetWidth() / 2, 0, Window->GetWidth() / 2, Window->GetHeight() / 2, false);
#if defined (APP_EDITOR_MODE)
	DrawScreenQuad();
#endif
	OnDrawEvent.Broadcast(deltaTime);
	//PhysicsSystem->Update(deltaTime);
	//PhysicsSystemPhysX->Update(deltaTime);
	Renderer->EndFrame();


	
}

void UApplication::DrawScene(float deltaTime)
{
	OnDrawEvent.Broadcast(deltaTime);
}

void UApplication::DrawScreenQuad()
{
	Renderer->DrawScreenQuad();
}

void UApplication::Loop()
{
	float deltaTime = 0.f;
	FTime currentTime = FTime::Now();

	auto TickFunction = [](float delta)
	{
		us::env::Environment::TickComponent->Tick(delta);
	};

	while (!Window->ShouldClose())
	{
		Window->MakeCurrent();
		Window->StartLoop();

		Window->PollEvents();
		CalculeDeltaTime(currentTime, deltaTime);

		ThreadTickEvent = new TThread(TickFunction, deltaTime);

		auto view = ECS.view<UUpdateComponent>();

		for (auto entity : view) 
		{
			auto& vel = view.get<UUpdateComponent>(entity);
			vel.OnUpdateCalledEvent.Broadcast(deltaTime);
		}

		//OnUpdateEvent.Broadcast(deltaTime);
		/*PhysicsSystem->Update(deltaTime);*/

		Draw(deltaTime);

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
	DeltaTime = deltaTime; //refactory
}

void UApplication::Run()
{
	Construct();
	PostConstruct();

	Initialize();
	PostInitialize();

	Loop();
}