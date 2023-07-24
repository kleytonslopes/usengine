/*********************************************************************
 *   File: Actor.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Actors/Actor.hpp"

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

	for (it = components.begin(); it != components.end(); it++)
	{
		it->second->Destroy();
		delete it->second;
	}

	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroy!", Identity.c_str()));
}

void AActor::Create()
{
	UTransformComponent* TransformComponent = AddComponent<UTransformComponent>();
	TransformComponent->SetOwner(Owner);
	TransformComponent->SetParent(this);
}
