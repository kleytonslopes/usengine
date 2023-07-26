/*********************************************************************
 *   File: Scene.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Framework/Scene.hpp"
#include "Renderer/OpenGL/RendererOpenGL.hpp"
#include "Runtime/Application.hpp"
#include "Camera/Camera.hpp"
#include "Actors/Actor.hpp"
#include "Actors/Entity.hpp"
#include "Pawns/Pawn.hpp"
#include "Input/InputManagement.hpp"
#include "Serializers/SceneSerializer.hpp"
#include "Runtime/Application.hpp"

#include "Components/CameraComponent.hpp"
#include "Components/MeshComponent.hpp"

UScene::UScene()
{
	Create();
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
	//* act = GetApplication()->RegistryClass<AActor>();
	Camera = UUniquePtr<ACamera>::Make();
	Camera.Get()->Create();
	entities[Camera.Get()->Id] = Camera.Get();

	DefaultPawn = UUniquePtr<APawn>::Make();
	DefaultPawn.Get()->Initialize();

	{
		AEntity* entity1 = CreateEntity<AEntity>();
		entity1->Initialize();

		AActor* actor1 = CreateEntity<AActor>();
		actor1->AddComponent<UCameraComponent>();
		UMeshComponent* meshComp = actor1->AddComponent<UMeshComponent>();

		FMeshParameters peshParameters{};
		peshParameters.MeshPath = "mesh123.obj";
		meshComp->SetMeshParameters(peshParameters);

		actor1->Initialize();
	}

	GetInputManagement()->SetInputComponent(DefaultPawn.Get()->GetInputComponent());

	SaveScene();

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

template<class T>
T* UScene::CreateEntity()
{
	T* newEntity = new T();
	newEntity->Create();

	entities[newEntity->Id] = newEntity;

	return newEntity;
}

void UScene::Create()
{
	Serializer = UUniquePtr<FSceneSerializer>::Make();
	Serializer.Get()->SetScene(this);
}

void UScene::SaveScene()
{
	Serializer.Get()->Serialize();
}

bool UScene::LoadScene(const FString& sceneName)
{
	return Serializer.Get()->Deserialize(sceneName);
}
