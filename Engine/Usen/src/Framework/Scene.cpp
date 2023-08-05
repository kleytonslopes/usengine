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
#include "Input/InputManagement.hpp"
#include "Serializers/SceneSerializer.hpp"
#include "Runtime/Application.hpp"

#include "Mesh/Mesh.hpp"

#include "Components/CameraComponent.hpp"
#include "Components/MeshComponent.hpp"

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
	DefaultPawn = UUniquePtr<APawn>::Make();
	DefaultPawn.Get()->Initialize();
	GetInputManagement()->SetInputComponent(DefaultPawn.Get()->GetInputComponent());

	GameMode.Get()->Initialize();
	//Controller.Get()->Initialize();

	URendererOpenGL* Renderer = GetRenderer<URendererOpenGL>();
	if (!Renderer)
		FException::RuntimeError("Renderer not Initialized!");

	LoadScene("Unnamed");
	//initialize shaders


	FShaderParameters shaderParameters{};
	UShaderOpenGL* shaderDefault = Renderer->CreateShader<UShaderOpenGL>(shaderParameters);


	

	{
		FTransform trasformC;
		trasformC.Location = { 500.f,0.f,0.f };
		Camera = CreateEntity<ACamera>();
		Camera->SetTransform(trasformC);
		Camera->Initialize();

		AEntity* entity1 = CreateEntity<AEntity>();
		entity1->Initialize();

		FTransform trasform;
		trasform.Location = { 0.f,0.f,0.f };
		trasform.Rotation = { 0.f,0.f,0.f };
		AActor* actor1 = CreateEntity<AActor>();
		actor1->SetTransform(trasform);

		FMeshParameters peshParameters{};
		peshParameters.MeshPath = FText::Format(Content::ModelFilePath, "plane.obj");
		FAttachmentSettings att{};
		AMesh* mesh = CreateEntity<AMesh>();
		mesh->AttatchTo(actor1, att);
		mesh->SetMeshParameters(peshParameters);

		FMeshParameters peshParameters2{};
		peshParameters2.MeshPath = FText::Format(Content::ModelFilePath, "cube.obj");
		AMesh* mesh1 = CreateEntity<AMesh>();
		mesh1->SetMeshParameters(peshParameters2);

		actor1->Initialize();
		mesh1->Initialize();
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
		//Super::Application->GetRenderer()->Draw(it->second, deltaTime);
	}

	Super::Application->GetRenderer()->EndFrame();
}

ACamera* UScene::GetCamera()
{
	return Camera;
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
	GameMode = USharedPtr<UGameModeBase>::Make();
	GameMode.Get()->Create();

	GetApplication()->OnUpdateEvent.Add(this, &This::Update);
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
