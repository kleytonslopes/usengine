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
	ULOG(ELogLevel::ELL_WARNING, FText::Format("[%s] - %s Destroyed!", Id.c_str(), Identity.c_str()));
}

void IWeakClass::Construct()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("[%s] - %s Constructing...", Id.c_str(), Identity.c_str()));
	if (bIsConstructed)
	{
		FException::RuntimeError(FText::Format("[%s] - %s Already Created!", Id.c_str(), GetIdentity().c_str()));
	}

}
void IWeakClass::PostConstruct()
{
	if (bCanTick)
		us::env::Environment::TickComponent->Register(this, &IWeakClass::Tick);

	bIsConstructed = true;
	ULOG(ELogLevel::ELL_SUCCESS, FText::Format("[%s] - %s Constructed", Id.c_str(), Identity.c_str()));
}

void IWeakClass::Initialize()
{
	if (!bIsConstructed)
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
	ULOG(ELogLevel::ELL_WARNING, FText::Format("[%s] - %s Destroy Called!", Id.c_str(), Identity.c_str()));
}
void IWeakClass::PostDestroy()
{
	bIsDestroyed = true;
}

void IWeakClass::Tick(float deltaTime)
{

}
