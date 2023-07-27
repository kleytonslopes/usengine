/*********************************************************************
 *   File: Actor.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: July 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Actors/Actor.hpp"
#include "Components/Component.hpp"
#include "Components/RenderComponent.hpp"

AActor::AActor()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

AActor::~AActor()
{


	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void AActor::Destroy()
{
	TMap<FString, AComponent*>::iterator it;

	for (it = components.begin(); it != components.end(); it++)
	{
		it->second->Destroy();
		delete it->second;
	}

	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroy!", Identity.c_str()));
}

void AActor::Create()
{
	UTransformComponent* TransformComponent = AddComponent<UTransformComponent>();
	TransformComponent->SetOwner(Owner);
	TransformComponent->SetParent(this);
}

void AActor::AttatchTo(AEntity* parent, FAttachmentSettings& attachmentSettings)
{
	Super::AttatchTo(parent, attachmentSettings);

	if (attachmentSettings.AttachMode == EAttachMode::EAM_SnapToTarget)
	{
		AActor* actorParent = GetParent<AActor>();
		if (actorParent)
		{
			SetTransform(actorParent->GetTransform());
		}
	}
}

void AActor::SetTransform(const FTransform& transform)
{
	UTransformComponent* TransformComponent = GetComponent<UTransformComponent>();
	TransformComponent->SetTransform(transform);
}

FVector AActor::GetLocation()
{
	UTransformComponent* TransformComponent = GetComponent<UTransformComponent>();

	return TransformComponent->GetLocation();
}

FVector AActor::GetSceneLocation()
{
	UTransformComponent* TransformComponent = GetComponent<UTransformComponent>();
	FVector location = TransformComponent->GetLocation();
	if (bIsAttached)
	{
		AActor* actorParent = GetParent<AActor>();
		if (actorParent)
		{
			FVector parentLocation = actorParent->GetLocation();
			location += parentLocation;
		}
	}
	return location;
}

FTransform& AActor::GetTransform()
{
	return GetComponent<UTransformComponent>()->GetTransform();
}

void AActor::Draw(float deltaTime)
{
	URenderComponent* RenderComponent = GetComponent<URenderComponent>();
	if (RenderComponent)
	{
		RenderComponent->Draw(deltaTime);
	}
}

void AActor::Serialize(SeriFile& otherOut)
{
	Super::Serialize(otherOut);

	Key(otherOut, "Components");
	BeginSection(otherOut);

	TMap<FString, AComponent*>::iterator it;
	for (it = components.begin(); it != components.end(); it++)
	{
		it->second->Serialize(otherOut);
	}

	EndSection(otherOut);
}
