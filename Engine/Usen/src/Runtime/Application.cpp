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

UApplication::UApplication()
{

}

UApplication::~UApplication()
{

}

void UApplication::Initialize()
{
	if (!window) window = USharedPtr<UWindow>::Make(this);

	OnInitialized();
}

void UApplication::OnInitialized()
{
	GetWindow()->Initialize();
}

void UApplication::Update(float deltaTime)
{
	GetWindow()->Update(deltaTime);
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
}

void UApplication::CalculeDeltaTime(FTime& currentTime, float& deltaTime)
{
	FTime newTime = FClock::Now();
	deltaTime = FClock::Duration(newTime, currentTime);
	currentTime = newTime;
}
