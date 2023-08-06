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

#include "Mesh/Mesh.hpp"
#include "Mesh/StaticMesh.hpp"

#include "Components/CameraComponent.hpp"
#include "Components/MeshComponent.hpp"

#include "Serializers/Serializer.hpp"

UScene::UScene()
{
	
}

UScene::~UScene()
{

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
	GameMode.Get()->Initialize();

	CreateDefaultPawn();

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
			FTransform trasformCamera;
			trasformCamera.Location = { 0.f,0.f,0.f };
			trasformCamera.Origin = { -25.f,0.f,5.f };
			trasformCamera.Rotation = { 0.f,0.f,0.f };
			Camera = CreateEntity<ACamera>();
			Camera->SetTransform(trasformCamera);
			Camera->Initialize();
			Camera->AttatchTo(Pawn, pawnCameraAttachmentSettings);

			FMeshParameters pawnMeshParameters{};
			FAttachmentSettings pawnMeshAttachmentSettings{};
			pawnMeshParameters.MeshPath = FText::Format(Content::ModelFilePath, "cube.obj");
			AMesh* pawnMesh = CreateEntity<AMesh>();
			pawnMesh->AttatchTo(Pawn, pawnMeshAttachmentSettings);
			pawnMesh->SetMeshParameters(pawnMeshParameters);
			pawnMesh->Initialize();
		}
	}

	SaveScene();

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
	return GameMode.Get();
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
	GetApplication()->OnUpdateEvent.Add(this, &This::Update);

	GameMode = USharedPtr<UGameModeBase>::Make();
	GameMode.Get()->Create();

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

void UScene::CreateDefaultPawn()
{
	//ACharacter* character = new ACharacter();
	//APawn* p1 = new APawn();
	//APawn* p2 = new APawn(*p1);

	//TClassOf<APawn> DefaultPlayerPawn = GameMode.Get()->GetDefaultPlayerPawn();
	////APawn* pa = DefaultPlayerPawn.GetNew();

	//APawn* PlayerPawn = CreateEntity<APawn>(DefaultPlayerPawn);
}
