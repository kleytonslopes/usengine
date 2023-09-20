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
#include "Renderer/Renderer.hpp"

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
	Attachments->SetOwner(this);

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

	if (CollisionComponent)
	{
		FVector worldLocation = CollisionComponent->GetWorldPosition();
		SetLocation(worldLocation + GetOrigin());
	}

	if (bDrawDebug)
	{
		FVector location = GetLocation();
		FVector fwrd = GetForwardVector();
		FVector locationY = location; locationY.y += 10.f;
		FVector locationX = location; locationX.x += 10.f;
		FVector locationZ = location; locationZ.z += 10.f;

		GetRenderer()->DebugDrawLine(location, locationX, FColor::Red);
		GetRenderer()->DebugDrawLine(location, locationY, FColor::Green);
		GetRenderer()->DebugDrawLine(location, locationZ, FColor::Blue);

		GetRenderer()->DebugDrawLine(location, location + fwrd, FColor::Purple);
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

	actorParent->OnLocationChangedEvent.Add(this, &This::SetLocationFromParent);

	actorParent->Attachments->Attatch(this);

	bControlParentRotation = attachmentSettings.bControlParentRotation;

	if (attachmentSettings.AttachMode == EAttachMode::EAM_SnapToTarget)
	{
		FTransform newTransform = actorParent->GetTransform();
		FVector location = newTransform.GetLocation();
		newTransform.SetLocation(location + GetOrigin());
		SetTransform(newTransform);
	}
	else if (attachmentSettings.AttachMode == EAttachMode::EAM_KeepTrasform)
	{
		FTransform parentTransform = actorParent->GetTransform();
		FVector location = parentTransform.GetLocation();
		FTransform myTransform = GetTransform();
		myTransform.SetLocation(location + myTransform.GetOrigin());
		//myTransform.Location = location + myTransform.Origin;
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
}
void AActor::SetLocation(FVector& vector)
{
	if (CollisionComponent)
		CollisionComponent->SetLocation(vector);
	else
		TransformComponent->SetLocation(vector);

}
void AActor::SetRotation(FVector& vector)
{
	//if (CollisionComponent)
	//	CollisionComponent->SetRotation(vector);
	//else
	TransformComponent->SetRotation(vector);
}
void AActor::SetScale(FVector& vector)
{
	TransformComponent->SetScale(vector);
}
void AActor::SetTransform(FTransform& transform)
{
	TransformComponent->SetTransform(transform);
}

void AActor::SetForwardVector(FVector& vector)
{
	TransformComponent->SetForwardVector(vector);
}

void AActor::SetUpVector(FVector& vector)
{
	//if (CollisionComponent)
	//	CollisionComponent->SetUpVector(vector);
	//else
	TransformComponent->SetUpVector(vector);
}

FVector AActor::GetOrigin()
{
	return TransformComponent->GetOrigin();
}

FVector AActor::GetLocation()
{
	if (CollisionComponent)
		return CollisionComponent->GetWorldPosition();
	else
		return TransformComponent->GetLocation();
}
FVector AActor::GetWorldLocation()
{
	return TransformComponent->GetWorldLocation();
}
FVector AActor::GetRotation()
{
	if (CollisionComponent)
		return CollisionComponent->GetRotation();
	else
		return TransformComponent->GetRotation();
	//return TransformComponent->GetRotation();
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
	if (CollisionComponent)
		return CollisionComponent->GetForwardVector();
	else
		return TransformComponent->GetForwardVector();
}
FVector AActor::GetRightVector()
{
	if (CollisionComponent)
		return CollisionComponent->GetRightVector();
	else
		return TransformComponent->GetRightVector();
}

FVector AActor::GetUpVector()
{
	return TransformComponent->GetUpVector();
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

void AActor::SetLocationFromParent(FVector newLocation)
{
	SetLocation(newLocation);
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
