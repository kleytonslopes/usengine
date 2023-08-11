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
#include "Framework/GameModeBase.hpp"

#include "Renderer/Renderer.hpp"
#include "Renderer/OpenGL/RendererOpenGL.hpp"
#include "Renderer/OpenGL/ShaderOpenGL.hpp"
#include "Renderer/ShaderParameters.hpp"
#include "Renderer/Shader.hpp"

#include "Runtime/Application.hpp"
#include "Camera/Camera.hpp"

#include "Actors/Actor.hpp"
#include "Actors/Entity.hpp"

#include "Pawns/Pawn.hpp"
#include "Pawns/Character.hpp"

#include "Input/InputManagement.hpp"
#include "Serializers/SceneSerializer.hpp"
#include "Runtime/Application.hpp"

#include "Controllers/Controller.hpp"
#include "Controllers/PlayerController.hpp"

#include "Mesh/Mesh.hpp"
#include "Mesh/StaticMesh.hpp"

#include "Components/CameraComponent.hpp"
#include "Components/MeshComponent.hpp"

#include "Serializers/Serializer.hpp"

DEFAULT_BODY(UScene)

void UScene::Destroy()
{
	if (bIsDestroyed)
		return;

	TMap<FString, AEntity*>::iterator it;

	for (it = entities.begin(); it != entities.end(); it++)
	{
		if (it->second->IsValid())
			FConstructorHelper::Destroy(it->second);
	}

	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroy!", Identity.c_str()));

	Super::Destroy();
}

void UScene::Initialize()
{
	GameMode->Initialize();

	URendererOpenGL* Renderer = GetRenderer<URendererOpenGL>();
	if (!Renderer)
		FException::RuntimeError("Renderer not Initialized!");

	LoadScene("Unnamed");

	// Prepare Shaders
	for (auto& shader : Settings.ShadersParameters)
	{
		Renderer->CreateShader<UShaderOpenGL>(shader);
	}


	/* */

	{
		{ // Floor
			FMeshParameters floorMeshParameters{};
			floorMeshParameters.MeshPath = FText::Format(Content::ModelFilePath, "sm_floor.obj");

			UStaticMesh* FloorMesh = CreateEntity<UStaticMesh>();
			FloorMesh->SetMeshParameters(floorMeshParameters);
			FloorMesh->Initialize();
		}
		{ // Gizmo
			FTransform trasform;
			trasform.Location = { 0.f,0.f,0.f };
			trasform.Rotation = { 0.f,0.f,0.f };
			FMeshParameters gizmoMeshParameters{};
			gizmoMeshParameters.MeshPath = FText::Format(Content::ModelFilePath, "gizmo.obj");
			AMesh* GizmoMesh = CreateEntity<AMesh>();
			GizmoMesh->SetIsDynamic(false);
			GizmoMesh->SetTransform(trasform);
			GizmoMesh->SetMeshParameters(gizmoMeshParameters);
			GizmoMesh->Initialize();
		}

		{ // Pawn
			APawn* Pawn = GetController()->GetPawn();
			Pawn->SetLocation(FVector{ 0.f,0.f,2.f });
			FAttachmentSettings pawnCameraAttachmentSettings{};
			pawnCameraAttachmentSettings.AttachMode = EAttachMode::EAM_KeepTrasform;
			Camera->Initialize();
			Camera->AttatchTo(Pawn, pawnCameraAttachmentSettings);

			///FTransform trasformCamera;
			///trasformCamera.Location = { 0.f,0.f,0.f };
			///trasformCamera.Origin = { -25.f,0.f,5.f };
			///trasformCamera.Rotation = { 0.f,0.f,0.f };
			///Camera = CreateEntity<ACamera>();
			///Camera->SetTransform(trasformCamera);
			///Camera->Initialize();
			///Camera->AttatchTo(Pawn, pawnCameraAttachmentSettings);

			FMeshParameters pawnMeshParameters{};
			FAttachmentSettings pawnMeshAttachmentSettings{};
			pawnMeshParameters.MeshPath = FText::Format(Content::ModelFilePath, "cube.obj");
			AMesh* pawnMesh = CreateEntity<AMesh>();
			pawnMesh->AttatchTo(Pawn, pawnMeshAttachmentSettings);
			pawnMesh->SetMeshParameters(pawnMeshParameters);
			pawnMesh->Initialize();
		}
	}

	//SaveScene();

	Super::Initialize();
}

void UScene::Update(float deltaTime)
{
	TMap<FString, AEntity*>::iterator it;

	Super::Application->GetRenderer()->StartFrame();

	for (it = entities.begin(); it != entities.end(); it++)
	{
		it->second->Update(deltaTime);
	}

	Super::Application->GetRenderer()->EndFrame();
}

ACamera* UScene::GetCamera()
{
	return Camera;
}

UGameModeBase* UScene::GetGameMode()
{
	return GameMode;
}

template<class T>
T* UScene::CreateEntity()
{
	T* newEntity = FConstructorHelper::CreateObject<T>();// new T();

	entities[newEntity->Id] = newEntity;

	return newEntity;
}

template<class T, class U>
T* UScene::CreateEntity(U& entityClass)
{
	T* newEntity = FConstructorHelper::CreateObject<T>(entityClass);
	//T* newEntity = std::move(entityClass.Class);//FConstructorHelper::CreateObject<U>(entityClass);//new U(*entityClass.Class);//entityClass.GetNew();
	//newEntity->Construct();
	//newEntity->PostConstruct();
	entities[newEntity->Id] = newEntity;

	return newEntity;
}

void UScene::PostConstruct()
{
	GameMode = FConstructorHelper::CreateObject<UGameModeBase>(GameModeClass);

	Serializer = FConstructorHelper::CreateObject<FSceneSerializer>();
	Serializer->SetScene(this);

	GetApplication()->OnUpdateEvent.Add(this, &This::Update);

	CreateDefaultCamera();
	CreateDefaultController();
	CreateDefaultPawn();

	Super::PostConstruct();
}

void UScene::Construct()
{
	FConstructorHelper::MakeClassOf<UGameModeBase>(GameModeClass);
	//GameModeClass = FConstructorHelper::GetClassOf<UGameModeBase>(GameModeClass);

	Super::Construct();
}

void UScene::SaveScene()
{
	Serializer->Serialize();
}

bool UScene::LoadScene(const FString& sceneName)
{
	return Serializer->Deserialize(sceneName);
}

void UScene::CreateDefaultPawn()
{
	TClassOf<APawn> DefaultPlayerPawnClass = GameMode->GetDefaultPlayerPawn();
	APawn* PlayerPawn = CreateEntity<APawn>(DefaultPlayerPawnClass);

	GameMode->SetPlayerPawn(PlayerPawn);
	GameMode->Controller->SetPawn(PlayerPawn);
}

void UScene::CreateDefaultController()
{
	TClassOf<UController> DefaultControllerClass = GameMode->GetDefaultController();
	UController* Controller = CreateEntity<UController>(DefaultControllerClass);

	GameMode->SetController(Controller);
}

void UScene::CreateDefaultCamera()
{
	FTransform trasformCamera;
	trasformCamera.Location = { 0.f,0.f,0.f };
	trasformCamera.Origin = { -25.f,0.f,5.f };
	trasformCamera.Rotation = { 0.f,0.f,0.f };
	Camera = CreateEntity<ACamera>();
	Camera->SetTransform(trasformCamera);
	Camera->Initialize();
}
