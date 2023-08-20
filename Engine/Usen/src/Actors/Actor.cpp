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
		if (Parent->IsValid())
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
		if (CollisionComponent)
		{
			CollisionComponent->SetLocation(TransformComponent->GetLocation());
		}

		ComponentsMap::iterator it;
		for (it = components.begin(); it != components.end(); it++)
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
	{
		SetTransform(actorParent->GetTransform());
	}
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
	TransformComponent->SetOrigin(vector);

	//if (CollisionComponent)
	//{
	//	FVector location = CollisionComponent->GetComponentLocation();
	//	TransformComponent->SetOrigin(location);
	//}
	//else
	//{
	//	if (AttachmentSettings.AttachMode == EAttachMode::EAM_SnapToTarget)
	//	{
	//		TransformComponent->SetOrigin(vector);
	//	}
	//	else if (AttachmentSettings.AttachMode == EAttachMode::EAM_KeepTrasform)
	//	{
	//		AActor* MyParent = GetParent<AActor>();
	//		FVector location = MyParent->GetLocation();
	//		FTransform myTransform = GetTransform();
	//
	//		myTransform.Location = location + myTransform.Origin;
	//		TransformComponent->SetLocation(myTransform.Location);
	//	}
	//}
}
void AActor::SetLocation(FVector& vector)
{
	if (CollisionComponent)
	{
		FVector lastLocation = TransformComponent->GetLocation();
		if (lastLocation != vector)
		{
			CollisionComponent->SetLocation(vector);
			TransformComponent->SetLocation(vector);
		}
	}
	else
	{
		TransformComponent->SetLocation(vector);
	}

	/*FVector newLocation = vector;

	if (CollisionComponent)
	{
		CollisionComponent->SetLocation(vector);
		newLocation = CollisionComponent->GetComponentLocation();
		TransformComponent->SetLocation(newLocation);

	}
	else
	{
		if (AttachmentSettings.AttachMode == EAttachMode::EAM_SnapToTarget)
		{
			if (CollisionComponent)
				CollisionComponent->SetLocation(vector);

			newLocation = CollisionComponent ? CollisionComponent->GetComponentLocation() : vector;
			TransformComponent->SetLocation(newLocation);
		}
		else if (AttachmentSettings.AttachMode == EAttachMode::EAM_KeepTrasform)
		{
			AActor* pParent = GetParent<AActor>();
			FVector pLocation = pParent->GetLocation();

			FTransform myTransform = GetTransform();

			myTransform.Location = pLocation + myTransform.Origin;
			if (CollisionComponent)
				CollisionComponent->SetLocation(myTransform.Location);

			TransformComponent->SetLocation(myTransform.Location);
		}

		if (Attachments->HasAttachments())
		{
			for (auto& it : Attachments->Attachments)
			{
				it.second->SetLocation(newLocation);
			}
		}
	}*/
}
void AActor::SetRotation(FVector& vector)
{
	//if (CollisionComponent)//veresse
	//{
	//	TransformComponent->SetRotation(vector);
	//}
	//else
	//{
	TransformComponent->SetRotation(vector);

	//}


	//TransformComponent->SetRotation(vector);

	//if (AttachmentSettings.AttachMode == EAttachMode::EAM_SnapToTarget)
	//{
	//	TransformComponent->SetRotation(vector);
	//}
	//else if (AttachmentSettings.AttachMode == EAttachMode::EAM_KeepTrasform)
	//{
	//	AActor* pParent = GetParent<AActor>();
	//	FVector pRotation = pParent->GetRotation();

	//	FTransform myTransform = GetTransform();
	//	//FVector myRotation = GetRotation();

	//	myTransform.Rotation = pRotation + myTransform.Rotation;
	//	TransformComponent->SetRotation(myTransform.Rotation);
	//}
}
void AActor::SetScale(FVector& vector)
{
	TransformComponent->SetScale(vector);
	//if (AttachmentSettings.AttachMode == EAttachMode::EAM_SnapToTarget)
	//{
	//	TransformComponent->SetScale(vector);
	//}
	//else if (AttachmentSettings.AttachMode == EAttachMode::EAM_KeepTrasform)
	//{
	//	AActor* pParent = GetParent<AActor>();
	//	FVector pScale = pParent->GetScale();

	//	FTransform myTransform = GetTransform();
	//	//FVector myScale = GetScale();

	//	myTransform.Scale = pScale + myTransform.Scale;
	//	TransformComponent->SetScale(myTransform.Scale);
	//}
}
void AActor::SetTransform(FTransform& transform)
{
	//if (CollisionComponent)
	//{
	//	CollisionComponent->SetLocation(transform.Location);
	//}
	TransformComponent->SetLocation(transform.Location);
	//if (CollisionComponent)
	//{
	//	FVector location = CollisionComponent->GetComponentLocation();
	//	TransformComponent->SetLocation(location);
	//}
	//else
	//{
	//	if (AttachmentSettings.AttachMode == EAttachMode::EAM_SnapToTarget)
	//	{
	//		TransformComponent->SetTransform(transform);
	//	}
	//	else if (AttachmentSettings.AttachMode == EAttachMode::EAM_KeepTrasform)
	//	{
	//		AActor* MyParent = GetParent<AActor>();
	//		FTransform parentTransform = MyParent->GetTransform();
	//		FVector location = parentTransform.Location;
	//		FTransform myTransform = GetTransform();

	//		myTransform.Location = location + myTransform.Origin;
	//		TransformComponent->SetTransform(myTransform);
	//	}
	//}

	//if (Attachments->HasAttachments())
	//{
	//	for (auto& it : Attachments->Attachments)
	//	{
	//		it.second->SetTransform(transform);
	//	}
	//}
}

void AActor::SetForwardVector(FVector& vector)
{
	TransformComponent->SetForwardVector(vector);
}

FVector AActor::GetLocation()
{
	//if (CollisionComponent)
	//{
	//	return CollisionComponent->GetComponentLocation();
	//}
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
	return TransformComponent->GetTransform();
}
FVector AActor::GetForwardVector()
{
	return TransformComponent->GetForwardVector();
}
FVector AActor::GetRightVector()
{
	return TransformComponent->GetRightVector();
}

UCollisionComponent* AActor::GetCollisionComponent()
{
	return CollisionComponent;
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
		if (it->second)
			it->second->Serialize(otherOut);
		else
			ULOG_Error(FText::Format("Failed to Save %s of %s", it->first.c_str(), Identity.c_str()));
	}

	EndSection(otherOut);
}
