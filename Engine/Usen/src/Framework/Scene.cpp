/*********************************************************************
 *   File: Scene.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Framework/Scene.hpp"
#include "Renderer/OpenGL/RendererOpenGL.hpp"
#include "Runtime/Application.hpp"
#include "Camera/Camera.hpp"
#include "Actors/Actor.hpp"
#include "Pawns/Pawn.hpp"
#include "Input/InputManagement.hpp"

UScene::UScene()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UScene::~UScene()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UScene::Destroy()
{
	TMap<FString, AEntity*>::iterator it;

	for (it = entities.begin(); it != entities.end(); it++)
	{
		it->second->Destroy();
		delete it->second;
	}

	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroy!", Identity.c_str()));
}

void UScene::Initialize()
{
	Camera = UUniquePtr<ACamera>::Make();
	Camera.Get()->Create();

	DefaultPawn = UUniquePtr<APawn>::Make();
	DefaultPawn.Get()->Initialize();

	GetInputManagement()->SetInputComponent(DefaultPawn.Get()->GetInputComponent());

	Super::Initialize();
}

void UScene::Update(float deltaTime)
{
	TMap<FString, AEntity*>::iterator it;

	for (it = entities.begin(); it != entities.end(); it++)
	{
		Super::Application->GetRenderer()->Draw(it->second, deltaTime);
	}
}
