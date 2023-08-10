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
	if (bIsConstructed)
	{
		FException::RuntimeError(FText::Format("%s Already Created!", GetIdentity().c_str()));
	}

}
void IWeakClass::PostConstruct()
{
	if (bTick)
		us::env::Environment::TickComponent->Register(this, &IWeakClass::Tick);

	bIsConstructed = true;
}

void IWeakClass::Initialize()
{
	if (!bIsCreated)
		FException::RuntimeError(FText::Format("%s Not created!", Identity.c_str()));

	if (bIsInitialized)
		FException::RuntimeError(FText::Format("%s Already Initialized!", Identity.c_str()));
}
void IWeakClass::PostInitialize()
{
	bIsInitialized = true;
}

void IWeakClass::Destroy()
{

}
void IWeakClass::PostDestroy()
{
	bIsDestroyed = true;
}

void IWeakClass::Tick(float deltaTime)
{

}
