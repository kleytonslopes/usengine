/*********************************************************************
 *   File: Scene.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Framework/Scene.hpp"
#include "Framework/Entity.hpp"
#include "Renderer/Renderer.hpp"
#include "Runtime/Application.hpp"
#include "Camera/Camera.hpp"
#include "Mesh/StaticMesh.hpp"

#include "Components/MeshComponent.hpp"
#include "Components/RendererComponent.hpp"
#include "Serializer/SceneSerializer.hpp"

UScene::~UScene()
{
	if (!bIsDestroyed)
		OnDestroy();

	delete SceneSerializer;
}

void UScene::Initialize()
{
	ULOG(ELogLevel::ELL_TRACE, "Initializing Scene...");
	SceneSerializer = new USceneSerializer(this);
	LoadScene("EntryMap");

	activeCamera = CreateEntity<UCamera>();

	UStaticMesh* meshTemp = CreateEntity<UStaticMesh>();

	FMeshParameters meshParam{};
	meshParam.MeshPath = FText::Format(Content::ModelFilePath ,"cube.obj");
	meshTemp->SetMeshParameters(meshParam);
	
	SaveScene();

	OnInitialized();
}

void UScene::OnInitialized()
{
	if (entities.size() > 0)
	{
		for (auto& entity : entities)
		{
			entity.second->Initialize();
		}
	}
}

void UScene::Update(float deltaTime)
{
	if (entities.size() > 0)
	{
		for (auto& entity : entities)
		{
			if(entity.second->bTick)
				entity.second->Update(deltaTime);
			if (entity.second->HasComponent<URendererComponent>())
				GetRenderer()->Draw(entity.second, deltaTime);
		}
	}
}

void UScene::OnDestroy()
{
	Super::OnDestroy();

	if (entities.size() > 0)
	{
		for (auto& entity : entities)
		{
			entity.second->OnDestroy();

			delete entity.second;
		}
	}

	ULOG(ELogLevel::ELL_WARNING, "UScene Destroyed!");
}

void UScene::SaveScene()
{
	SceneSerializer->Serialize();
}

void UScene::LoadScene(const FString& scenePath)
{
	SceneSerializer->Deserialize(scenePath);
}

UCamera* UScene::GetCamera()
{
	return activeCamera;
}

template<typename T>
T* UScene::CreateEntity()
{
	T* newEntity = new T(this);
	newEntity->OnConstruct();

	entities[newEntity->Id] = newEntity;

	return newEntity;
}
