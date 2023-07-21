/*********************************************************************
 *   File: Application.cpp
 *  Brief:
 *
 * Author: Kleyton
 *   Date: July 2023
 *
 * Copyright (c) 2023 Sunydark. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Runtime/Application.hpp"
#include "Presentation/Window.hpp"
#include "Framework/GameInstance.hpp"
#include "Framework/Scene.hpp"
#include "Renderer/Renderer.hpp"

UApplication::UApplication()
{

}

UApplication::~UApplication()
{
	ULOG(ELogLevel::ELL_WARNING, "UApplication Destroyed!");
}

void UApplication::Initialize()
{
	ULOG(ELogLevel::ELL_TRACE, "Initializing Application...");
	if (!window) window = UUniquePtr<UWindow>::Make(this);
	if (!gameInstance) gameInstance = UUniquePtr<UGameInstance>::Make(this);
	if (!currentScene) currentScene = UUniquePtr<UScene>::Make(this);
	if (!renderer) renderer = UUniquePtr<URenderer>::Make(this);

	OnInitialized();
}

void UApplication::OnInitialized()
{
	GetWindow()->Initialize();
	GetGameInstance()->Initialize();
	GetRenderer()->Initialize();
	GetScene()->Initialize();
}

void UApplication::Update(float deltaTime)
{
	GetWindow()->Update(deltaTime);
	GetGameInstance()->Update(deltaTime);
	GetScene()->Update(deltaTime);
}

void UApplication::Run()
{
	Initialize();

	Loop();
}

UWindow* UApplication::GetWindow()
{
	return window.Get();
}

UGameInstance* UApplication::GetGameInstance()
{
	return gameInstance.Get();
}

URenderer* UApplication::GetRenderer()
{
	return renderer.Get();
}

UScene* UApplication::GetScene()
{
	return currentScene.Get();
}

void UApplication::Loop()
{
	float deltaTime = 0.f;
	FTime currentTime = FTime::Now();

	while (!GetWindow()->ShouldClose())
	{
		GetWindow()->StartLoop();

			GetWindow()->PollEvents();
			CalculeDeltaTime(currentTime, deltaTime);
			Update(deltaTime);

		GetWindow()->StopLoop();
	}

	GetGameInstance()->OnDestroy();
	GetWindow()->OnDestroy();
}

void UApplication::CalculeDeltaTime(FTime& currentTime, float& deltaTime)
{
	FTime newTime = FClock::Now();
	deltaTime = FClock::Duration(newTime, currentTime);
	currentTime = newTime;
}
