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
#include "Core/Attachment.hpp"

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

	if (bIsAttached)
	{
		Parent->DetachFromParent();
	}

	for (it = components.begin(); it != components.end(); it++)
	{
		it->second->Destroy();
		delete it->second;
	}

	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroy!", Identity.c_str()));
}

void AActor::Create()
{
	Super::Create();

	Attachments = UUniquePtr<UAttachment>::Make();

	UTransformComponent* TransformComponent = AddComponent<UTransformComponent>();
	TransformComponent->SetOwner(Owner);
	TransformComponent->SetParent(this);

	PostCreate();
}

void AActor::Initialize()
{
	Super::Initialize();

	if (Attachments.Get()->HasAttachments())
	{
		Attachments.Get()->Initialize();
	}
}

void AActor::AttatchTo(AEntity* parent, FAttachmentSettings& attachmentSettings)
{
	if (!parent)
		return;

	Super::AttatchTo(parent, attachmentSettings);

	AActor* actorParent = GetParent<AActor>();

	if (!actorParent)
		return;

	actorParent->Attachments.Get()->Attatch(this);
	
	if (attachmentSettings.AttachMode == EAttachMode::EAM_SnapToTarget)
		SetTransform(actorParent->GetTransform());
	else if (attachmentSettings.AttachMode == EAttachMode::EAM_KeepTrasform)
	{
		FTransform parentTransform = actorParent->GetTransform();
		FVector location = parentTransform.Location;
		FTransform myTransform = GetTransform();
		myTransform.Location = location + myTransform.Origin;
		SetTransform(myTransform);
	}

}

void AActor::Detach(AActor* actor)
{
	Attachments.Get()->Detach(actor);
}

void AActor::DetachFromParent()
{
	Super::DetachFromParent();
	AActor* actorParent = GetParent<AActor>();

	if (actorParent)
	{
		actorParent->Attachments.Get()->Detach(this);
	}
}

void AActor::SetTransform(const FTransform& transform)
{
	UTransformComponent* TransformComponent = GetComponent<UTransformComponent>();
	
	if (AttachmentSettings.AttachMode == EAttachMode::EAM_SnapToTarget)
	{
		TransformComponent->SetTransform(transform);
	} 
	else if (AttachmentSettings.AttachMode == EAttachMode::EAM_KeepTrasform)
	{
		AActor* MyParent = GetParent<AActor>();
		FTransform parentTransform = MyParent->GetTransform();
		FVector location = parentTransform.Location;
		FTransform myTransform = GetTransform();

		myTransform.Location = location + myTransform.Origin;
		TransformComponent->SetTransform(myTransform);
	}

	if (Attachments.Get()->HasAttachments())
	{
		for (auto& it : Attachments.Get()->Attachments)
		{
			it.second->SetTransform(transform);
		}
	}
}

void AActor::Update(float deltaTime)
{
	Super::Update(deltaTime);

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
