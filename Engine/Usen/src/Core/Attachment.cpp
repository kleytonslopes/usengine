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
