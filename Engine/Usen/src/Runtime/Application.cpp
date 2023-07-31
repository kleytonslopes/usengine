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
#include "Environment.hpp"
#include "Controllers/Controller.hpp"
#include "Input/InputManagement.hpp"


UApplication::UApplication()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UApplication::~UApplication()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UApplication::Initialize()
{
	Window = UUniquePtr<UWindow>::Make();
	Window.Get()->Initialize();

	GameInstance = UUniquePtr<UGameInstance>::Make();
	GameInstance.Get()->Initialize();

	Renderer = UUniquePtr<BRenderer>::MakeCast<URendererOpenGL>();
	Renderer.Get()->Initialize();

	InputManagement = UUniquePtr<UInputManagement>::Make();
	InputManagement.Get()->Create();
	InputManagement.Get()->Initialize();

	Scene = UUniquePtr<UScene>::Make();
	Scene.Get()->Create();
	Scene.Get()->LoadScene("Unnamed");
	Scene.Get()->Initialize();

	Controller = UUniquePtr<UController>::Make();
	Controller.Get()->Create();
	Controller.Get()->Initialize();

	bIsInitialized = true;
}

void UApplication::PostInitialize()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s PostInitialize!", Identity.c_str()));
}

void UApplication::Destroy()
{
	Controller.Destroy();//.Get()->Destroy();
	Scene.Destroy();//.Get()->Destroy();
	InputManagement.Destroy();//.Get()->Destroy();
	GameInstance.Destroy();//.Get()->Destroy();
	Renderer.Destroy();//.Get()->Destroy();
	Window.Destroy();//.Get()->Destroy();

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
		Window.Get()->StartLoop();

		Window.Get()->PollEvents();
		CalculeDeltaTime(currentTime, deltaTime);

		Window.Get()->Update(deltaTime);
		GameInstance.Get()->Update(deltaTime);
		Scene.Get()->Update(deltaTime);

		Window.Get()->StopLoop();
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
	Initialize();
	Loop();
}