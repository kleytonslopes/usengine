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

void UScene::Construct()
{
	Super::Construct();

	bCanTick = false;
	bCanUpdate = true;

	FConstructorHelper::MakeClassOf<UGameModeBase>(GameModeClass);
}

void UScene::PostConstruct()
{
	Super::PostConstruct();

	GetApplication()->OnDrawEvent.Add(this, &This::DrawScene);

	GameMode = FConstructorHelper::CreateObject<UGameModeBase>(GameModeClass);

	Serializer = FConstructorHelper::CreateObject<FSceneSerializer>();
	Serializer->SetScene(this);

	CreateDefaultCamera();
	CreateDefaultController();
	CreateDefaultPawn();
}

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
	Camera->SetLocation(FVector{ 0.f, 23.0f, 10.f });
	Camera->SetRotation(FVector{ -64.f, 0.f, 0.f });

	/* */

	{
		//{ //Cube Sphere
		//	FTransform transformBox;
		//	transformBox.Location = { 0.f,0.f,0.f };
		//	transformBox.Origin = { 0.f,0.f,0.f };
		//	transformBox.Rotation = { 0.f,0.f,0.f };
		//	FMeshParameters boxMeshParameters{};
		//	boxMeshParameters.MeshPath = FText::Format(Content::ModelFilePath, "cube_sphere.obj");
		//	AMesh* boxMesh = CreateEntity<AMesh>();
		//	boxMesh->SetCanCollider(false);
		//	boxMesh->SetBoundBox(FVector{ 50.f, 50.f, 50.f });
		//	boxMesh->SetMeshParameters(boxMeshParameters);
		//	boxMesh->SetIsDynamic(false);
		//	boxMesh->SetLocation(transformBox.Location);
		//	boxMesh->Initialize();
		//}

		{ // Floor
			FMeshParameters floorMeshParameters{};
			floorMeshParameters.MeshPath = FText::Format(Content::ModelFilePath, "sm_floor.obj");
			FTransform trasform;
			trasform.Location = { 0.f,-5.f,0.f };
			trasform.Rotation = { 0.f,0.f,0.f };
			Floor = CreateEntity<UStaticMesh>();
			Floor->SetBoundBox(FVector{ 0.f, -0.1f, 0.0f });
			Floor->SetCollisionGroup(ECG_None);
			Floor->SetCollisionMask(ECM_None);
			Floor->SetLocation(trasform.Location);
			Floor->SetMeshParameters(floorMeshParameters);
			Floor->SetIsDynamic(false);
			Floor->Initialize();
		}

		//{ // Gizmo
		//	FTransform trasform;
		//	trasform.Location = { 0.f,0.f,0.f };
		//	trasform.Rotation = { 0.f,0.f,0.f };
		//	FMeshParameters gizmomeshparameters{};
		//	gizmomeshparameters.MeshPath = FText::Format(Content::ModelFilePath, "gizmo.obj");
		//	AMesh* gizmomesh = CreateEntity<AMesh>();
		//	gizmomesh->SetBoundBox(FVector{ 0.2f, 0.2f, 0.2f });
		//	gizmomesh->SetIsDynamic(false);
		//	gizmomesh->SetTransform(trasform);
		//	gizmomesh->SetMeshParameters(gizmomeshparameters);
		//	gizmomesh->Initialize();
		//}

		//{ // Pawn

		//	APawn* Pawn = GetController()->GetPawn();
		//	Pawn->SetLocation(FVector{ 0.f, 0.f, 10.f });

		//	FAttachmentSettings pawnCameraAttachmentSettings{};
		//	pawnCameraAttachmentSettings.AttachMode = EAttachMode::EAM_KeepTrasform;

		//	FMeshParameters pawnMeshParameters{};
		//	FAttachmentSettings pawnMeshAttachmentSettings{};
		//	pawnMeshParameters.MeshPath = FText::Format(Content::ModelFilePath, "cube.obj");
		//	//AMesh* pawnMesh = CreateEntity<AMesh>();
		//	//pawnMesh->SetIsDynamic(false);
		//	//pawnMesh->SetBoundBox(FVector{ 1.f, 1.f, 1.f });
		//	//pawnMesh->AttatchTo(Pawn, pawnMeshAttachmentSettings);
		//	//pawnMesh->SetMeshParameters(pawnMeshParameters);
		//	//pawnMesh->Initialize();
		//}

		//{ // Box

		//	FTransform transformBox;
		//	transformBox.Location = { 0.f,0.f,10.f };
		//	transformBox.Origin   = { 0.f,0.f,0.f };
		//	transformBox.Rotation = { 0.f,0.f,0.f };
		//	FMeshParameters boxMeshParameters{};
		//	boxMeshParameters.MeshPath = FText::Format(Content::ModelFilePath, "cube.obj");
		//	AMesh* boxMesh = CreateEntity<AMesh>();
		//	boxMesh->SetBoundBox(FVector{ 1.f, 1.f, 1.f });
		//	boxMesh->SetMeshParameters(boxMeshParameters);
		//	boxMesh->SetIsDynamic(true);
		//	boxMesh->SetLocation(transformBox.Location);
		//	boxMesh->Initialize();
		//}

		//{ // wall

		//	FTransform transformBox;
		//	transformBox.Location = { 0.f,10.f,0.f };
		//	transformBox.Origin = { 0.f,0.f,0.f };
		//	transformBox.Rotation = { 0.f,0.f,0.f };
		//	FMeshParameters boxMeshParameters{};
		//	boxMeshParameters.MeshPath = FText::Format(Content::ModelFilePath, "wall.obj");
		//	AMesh* boxMesh = CreateEntity<AMesh>();
		//	boxMesh->SetBoundBox(FVector{ 3.f, 0.2f, 3.f });
		//	boxMesh->SetMeshParameters(boxMeshParameters);
		//	boxMesh->SetIsDynamic(false);
		//	boxMesh->SetLocation(transformBox.Location);
		//	boxMesh->Initialize();
		//}
	}

	//SaveScene();

	Super::Initialize();
}

void UScene::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void UScene::DrawScene(float deltaTime)
{
	TMap<FString, AEntity*>::iterator it;

	for (it = entities.begin(); it != entities.end(); it++)
	{
		it->second->Draw(deltaTime);
	}
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
	T* newEntity = FConstructorHelper::CreateObject<T>();

	entities[newEntity->Id] = newEntity;

	return newEntity;
}

template<class T, class U>
T* UScene::CreateEntity(U& entityClass)
{
	T* newEntity = FConstructorHelper::CreateObject<T>(entityClass);
	entities[newEntity->Id] = newEntity;

	return newEntity;
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
