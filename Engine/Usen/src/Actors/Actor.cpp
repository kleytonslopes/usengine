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
#include "Components/CollisionComponent.hpp"
#include "Core/Attachment.hpp"

DEFAULT_BODY(AActor)

void AActor::Destroy()
{
	Super::Destroy();

	TMap<FString, AComponent*>::iterator it;

	if (bIsAttached)
	{
		if(Parent->IsValid())
			Parent->DetachFromParent();
	}

	for (it = components.begin(); it != components.end(); it++)
	{
		if (it->second != nullptr)
		{
			FConstructorHelper::Destroy(it->second);
		}
	}

	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroy!", Identity.c_str()));
}

void AActor::Construct()
{
	Super::Construct();

	bCanTick = true;

	Attachments = FConstructorHelper::CreateObject<UAttachment>();

	TransformComponent = AddComponent<UTransformComponent>();
}

void AActor::Initialize()
{
	Super::Initialize();

	if (Attachments->HasAttachments())
	{
		Attachments->Initialize();
	}

	if (components.size() > 0)
	{
		ComponentsMap::iterator it;
		for (it = components.begin() ; it != components.end() ; it++)
		{
			it->second->Construct();
			it->second->PostConstruct();

			it->second->Initialize();
			it->second->PostInitialize();
		}
	}
}

void AActor::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void AActor::AttatchTo(AEntity* parent, FAttachmentSettings& attachmentSettings)
{
	if (!parent)
		return;

	Super::AttatchTo(parent, attachmentSettings);

	AActor* actorParent = GetParent<AActor>();

	if (!actorParent)
		return;

	actorParent->Attachments->Attatch(this);

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
	Attachments->Detach(actor);
}

void AActor::DetachFromParent()
{
	Super::DetachFromParent();
	AActor* actorParent = GetParent<AActor>();

	if (actorParent)
	{
		actorParent->Attachments->Detach(this);
	}
}

void AActor::SetOrigin(FVector& vector)
{
	if (AttachmentSettings.AttachMode == EAttachMode::EAM_SnapToTarget)
	{
		TransformComponent->SetOrigin(vector);
	}
	else if (AttachmentSettings.AttachMode == EAttachMode::EAM_KeepTrasform)
	{
		AActor* MyParent = GetParent<AActor>();
		FVector location = MyParent->GetLocation();
		FTransform myTransform = GetTransform();
		//FVector myLocation = GetLocation();

		myTransform.Location = location + myTransform.Origin;
		TransformComponent->SetLocation(myTransform.Location);
	}
}
void AActor::SetLocation(FVector& vector)
{
	if (AttachmentSettings.AttachMode == EAttachMode::EAM_SnapToTarget)
	{
		TransformComponent->SetLocation(vector);
	}
	else if (AttachmentSettings.AttachMode == EAttachMode::EAM_KeepTrasform)
	{
		AActor* pParent = GetParent<AActor>();
		FVector pLocation = pParent->GetLocation();

		FTransform myTransform = GetTransform();
		//FVector myLocation = GetLocation();

		myTransform.Location = pLocation + myTransform.Origin;
		TransformComponent->SetLocation(myTransform.Location);
	}
}
void AActor::SetRotation(FVector& vector)
{
	if (AttachmentSettings.AttachMode == EAttachMode::EAM_SnapToTarget)
	{
		TransformComponent->SetRotation(vector);
	}
	else if (AttachmentSettings.AttachMode == EAttachMode::EAM_KeepTrasform)
	{
		AActor* pParent = GetParent<AActor>();
		FVector pRotation = pParent->GetRotation();

		FTransform myTransform = GetTransform();
		//FVector myRotation = GetRotation();

		myTransform.Rotation = pRotation + myTransform.Rotation;
		TransformComponent->SetRotation(myTransform.Rotation);
	}
}
void AActor::SetScale(FVector& vector)
{
	if (AttachmentSettings.AttachMode == EAttachMode::EAM_SnapToTarget)
	{
		TransformComponent->SetScale(vector);
	}
	else if (AttachmentSettings.AttachMode == EAttachMode::EAM_KeepTrasform)
	{
		AActor* pParent = GetParent<AActor>();
		FVector pScale = pParent->GetScale();

		FTransform myTransform = GetTransform();
		//FVector myScale = GetScale();

		myTransform.Scale = pScale + myTransform.Scale;
		TransformComponent->SetScale(myTransform.Scale);
	}
}
void AActor::SetTransform(FTransform& transform)
{
	///UTransformComponent* TransformComponent = GetComponent<UTransformComponent>();
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

	if (Attachments->HasAttachments())
	{
		for (auto& it : Attachments->Attachments)
		{
			it.second->SetTransform(transform);
		}
	}
}

FVector AActor::GetLocation()
{
	///UTransformComponent* TransformComponent = GetComponent<UTransformComponent>();

	return TransformComponent->GetLocation();
}

FVector AActor::GetRotation()
{
	return TransformComponent->GetRotation();
}

FVector AActor::GetScale()
{
	return TransformComponent->GetScale();
}

FVector AActor::GetSceneLocation()
{
	///UTransformComponent* TransformComponent = GetComponent<UTransformComponent>();
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
	return TransformComponent->GetTransform();//GetComponent<UTransformComponent>()->GetTransform();
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
