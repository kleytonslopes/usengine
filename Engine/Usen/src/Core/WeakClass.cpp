/*********************************************************************
 *   File: WeakClass.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Core/WeakClass.hpp"

void UWeakClass::Destroy()
{
	bWantDestroy = true;
}

void UWeakClass::OnDestroy()
{
	bIsDestroyed = true;
}