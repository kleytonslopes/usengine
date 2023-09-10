/*********************************************************************
 *   File: Attachment.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Core/Attachment.hpp"
#include "Actors/Actor.hpp"
#include "Actors/Entity.hpp"

DEFAULT_BODY(UAttachment)

bool UAttachment::HasAttachments() const
{
	return Attachments.size() > 0;
}

void UAttachment::Initialize()
{
	Attachments.empty();
	Super::Initialize();

	TMap<FString, AActor*>::iterator it;

	for (it = Attachments.begin(); it != Attachments.end(); it++)
	{
		it->second->Initialize();
	}
}

void UAttachment::SetOwner(AActor* owner)
{
	Owner = owner;
}

void UAttachment::UpdateLocation()
{
	if (!Owner)
		return;

	TMap<FString, AActor*>::iterator it;

	for (it = Attachments.begin(); it != Attachments.end(); it++)
	{
		if (it->second)
			it->second->SetLocation(Owner->GetLocation() + it->second->GetOrigin());
		else
			ULOG(ELogLevel::ELL_ERROR, FText::Format("Failed to update Attachment of actor: %s", Owner->GetIdentity().c_str()));
	}
}

void UAttachment::Attatch(AActor* actor)
{
	if (!actor)
		return;

	Attachments.emplace(actor->GetId(), actor);
}

bool UAttachment::Detach(AActor* actor)
{
	if (!actor)
		return false;

	TMap<FString, AActor*>::iterator it = Attachments.find(actor->GetId());

	if (it != Attachments.end())
	{
		Attachments.erase(actor->GetId());
		return true;
	}

	return false;
}
