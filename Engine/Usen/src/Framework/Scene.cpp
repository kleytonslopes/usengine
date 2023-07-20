#include "upch.hpp"
#include "Framework/Scene.hpp"
#include "Framework/Entity.hpp"
#include "Renderer/Renderer.hpp"
#include "Runtime/Application.hpp"

UScene::~UScene()
{
	if (!bIsDestroyed)
		OnDestroy();
}

void UScene::Initialize()
{
	ULOG(ELogLevel::ELL_TRACE, "Initializing Scene...");
}

void UScene::Update(float deltaTime)
{
	GetRenderer()->Draw();
}

void UScene::OnDestroy()
{
	Super::OnDestroy();

	if (entities.size() > 0)
	{
		for (auto& entity : entities)
		{
			entity.second->OnDestroy();
		}
	}

	ULOG(ELogLevel::ELL_WARNING, "UScene Destroyed!");
}