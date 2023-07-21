#include "upch.hpp"
#include "Framework/Scene.hpp"
#include "Framework/Entity.hpp"
#include "Renderer/Renderer.hpp"
#include "Runtime/Application.hpp"
#include "Camera/Camera.hpp"
#include "Mesh/StaticMesh.hpp"

#include "Components/MeshComponent.hpp"

UScene::~UScene()
{
	if (!bIsDestroyed)
		OnDestroy();
}

void UScene::Initialize()
{
	ULOG(ELogLevel::ELL_TRACE, "Initializing Scene...");

	activeCamera = CreateEntity<UCamera>();

	UStaticMesh* meshTemp = CreateEntity<UStaticMesh>();

	FMeshParameters meshParam{};
	meshParam.MeshPath = "../../Content/Models/cube.obj";
	meshTemp->SetMeshParameters(meshParam);

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
	GetRenderer()->Draw();

	if (entities.size() > 0)
	{
		for (auto& entity : entities)
		{
			if(entity.second->bTick)
				entity.second->Update(deltaTime);
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

template<typename T>
T* UScene::CreateEntity()
{
	T* newEntity = new T(this);
	newEntity->OnConstruct();

	entities[newEntity->Id] = newEntity;

	return newEntity;
}
