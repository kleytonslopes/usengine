/*********************************************************************
 *   File: Camera.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Camera/Camera.hpp"

#include "Components/CameraComponent.hpp"

void UCamera::OnConstruct()
{
	Super::OnConstruct();
	
	bTick = false;

	AddComponent<UCameraComponent>();
}
