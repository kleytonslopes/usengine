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

AEntity::AEntity()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created with id %s!", Identity.c_str(), Id.c_str()));
}

AEntity::~AEntity()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Created!", Identity.c_str()));
}

void AEntity::Create()
{
	Attachments = UUniquePtr<UAttachment>::Make();

	bIsCreated = true;
}

void AEntity::Destroy()
{
	if (Parent)
	{
		Parent->Detach(this);
	}
}

void AEntity::Initialize()
{
	Super::Initialize();

	if (!bIsCreated)
		return;

	if (Attachments.Get()->HasAttachments())
	{
		Attachments.Get()->Initialize();
	}
}

void AEntity::Update(float deltaTime)
{
	GetApplication()->GetRenderer()->Draw(this, deltaTime);
}

void AEntity::Serialize(SeriFile& otherOut)
{
	/* override */
}

void AEntity::SetOwner(AEntity* owner)
{
	this->Owner = owner;
}

void AEntity::AttatchTo(AEntity* parent, FAttachmentSettings& attachmentSettings)
{
	parent->Attachments.Get()->Attatch(this);
	this->Parent = parent;
	bIsAttached = true;
}

void AEntity::Detach(AEntity* entity)
{
	Attachments.Get()->Detach(entity);
}

void AEntity::Draw(float deltaTime)
{

}
