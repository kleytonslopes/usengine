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
#include "Actors/Entity.hpp"

UAttachment::UAttachment()
{
	Attachments.empty();
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UAttachment::~UAttachment()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

bool UAttachment::HasAttachments() const
{
	return Attachments.size() > 0;
}

void UAttachment::Initialize()
{
	Super::Initialize();

	TMap<FString, AEntity*>::iterator it;

	for (it = Attachments.begin(); it != Attachments.end(); it++)
	{
		it->second->Initialize();
	}
}

void UAttachment::Attatch(AEntity* entity)
{
	if (!entity)
		return;

	Attachments.emplace(entity->GetId(), entity);
}

bool UAttachment::Detach(AEntity* entity)
{
	if (!entity)
		return false;

	TMap<FString, AEntity*>::iterator it = Attachments.find(entity->GetId());

	if (it != Attachments.end())
	{
		Attachments.erase(entity->GetId());
		return true;
	}

	return false;
}
