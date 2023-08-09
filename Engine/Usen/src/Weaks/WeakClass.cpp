/*********************************************************************
 *   File: WeakClass.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Weaks/WeakClass.hpp"
#include "Core/Guid.hpp"
#include "Environment/Environment.hpp"

IWeakClass::IWeakClass()
{
	Id = FGuid::NewGuid();
}

IWeakClass::~IWeakClass()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void IWeakClass::Construct()
{
	if (bTick)
		us::env::Environment::TickComponent.Get()->Register(this, &IWeakClass::Tick);

	PostConstruct();
}
void IWeakClass::PostConstruct()
{
	bIsConstructed = true;
}

void IWeakClass::Create()
{
	if (!bIsConstructed)
		FException::RuntimeError(FText::Format("%s Not constructed!", Identity.c_str()));

	PostCreate();
}
void IWeakClass::PostCreate()
{
	bIsCreated = true;
}

void IWeakClass::Initialize()
{
	if (!bIsCreated)
		FException::RuntimeError(FText::Format("%s Not created!", Identity.c_str()));

	if (bIsInitialized)
		FException::RuntimeError(FText::Format("%s Already Initialized!", Identity.c_str()));

	PostInitialize();
}
void IWeakClass::PostInitialize()
{
	bIsInitialized = true;
}

void IWeakClass::Destroy()
{
	PostDestroy();
}
void IWeakClass::PostDestroy()
{
	bIsDestroyed = true;
}

void IWeakClass::Tick(float deltaTime)
{

}
