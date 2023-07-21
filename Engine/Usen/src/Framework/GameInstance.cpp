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

	OnInitialized();
}

void UGameInstance::OnInitialized()
{

}

void UGameInstance::Update(float deltaTime)
{

}

void UGameInstance::OnDestroy()
{
	Super::OnDestroy();

	ULOG(ELogLevel::ELL_WARNING, "UGameInstance Destroyed!");
}
