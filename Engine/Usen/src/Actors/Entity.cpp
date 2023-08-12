/*********************************************************************
 *   File: Entity.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Actors/Entity.hpp"
#include "Serializers/EntitySerializer.hpp"
#include "Core/Attachment.hpp"
#include "Runtime/Application.hpp"
#include "Environment/Environment.hpp"

DEFAULT_BODY(AEntity);

void AEntity::Construct()
{
	Super::Construct();
}

void AEntity::PostConstruct()
{
	Super::PostConstruct();

	if (bIsDrawable)
		us::env::Environment::RenderComponent->Register(this, &AEntity::Draw);
}

void AEntity::Update(float deltaTime)
{
	if (!bCanUpdate)
		return;

	//GetApplication()->GetRenderer()->Draw(this, deltaTime);
}

void AEntity::SetOwner(AEntity* owner)
{
	this->Owner = owner;
}

void AEntity::AttatchTo(AEntity* parent, FAttachmentSettings& attachmentSettings)
{
	AttachmentSettings = attachmentSettings;
	Parent = parent;
	bIsAttached = true;
}

void AEntity::DetachFromParent()
{
	Parent = nullptr;
	bIsAttached = false;
}

FString AEntity::GetParentId()
{
	return Parent != nullptr ? Parent->GetId() : "";
}

void AEntity::Draw(float deltaTime)
{
	ULOG(ELogLevel::ELL_TRACE, FText::Format("%s Draw...", this->GetId().c_str()));
}
