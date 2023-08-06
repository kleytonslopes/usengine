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
}

AEntity::~AEntity()
{
}

void AEntity::Create()
{
	if (bIsCreated)
	{
		FException::RuntimeError(FText::Format("%s Already Created!", GetIdentity().c_str()));
	}

	bIsCreated = true;
}

void AEntity::Destroy()
{

}

void AEntity::Initialize()
{
	Super::Initialize();

	if (!bIsCreated)
		return;

	//if (Attachments.Get()->HasAttachments())
	//{
	//	Attachments.Get()->Initialize();
	//}
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

}
