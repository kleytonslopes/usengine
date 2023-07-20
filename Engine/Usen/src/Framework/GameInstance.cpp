#include "upch.hpp"
#include "FrameWork/GameInstance.hpp"
#include "Runtime/Application.hpp"
#include "Framework/Scene.hpp"

UGameInstance::~UGameInstance()
{
	if (!bIsDestroyed)
		OnDestroy();
}

void UGameInstance::Initialize()
{
	ULOG(ELogLevel::ELL_TRACE, "Initializing GameInstance...");

	//currentScene = USharedPtr<UScene>::Make(application);

	OnInitialized();
}

void UGameInstance::OnInitialized()
{
	//GetScene()->Initialize();
}

void UGameInstance::Update(float deltaTime)
{
	//GetScene()->Update(deltaTime);
}

void UGameInstance::OnDestroy()
{
	Super::OnDestroy();

	//GetScene()->OnDestroy();

	ULOG(ELogLevel::ELL_WARNING, "UGameInstance Destroyed!");
}

//UScene* UGameInstance::GetScene()
//{
//	return currentScene.Get();
//}
