/*********************************************************************
 *   File: Camera.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Camera/Camera.hpp"
#include "Components/CameraComponent.hpp"

DEFAULT_BODY(ACamera);

void ACamera::Create()
{
	Super::Create();

	UCameraComponent* cameraComponent = AddComponent<UCameraComponent>();
	cameraComponent->SetOwner(Owner);
	cameraComponent->SetParent(this);
}

FMatrix4 ACamera::GetView()
{
	const FTransform& transform = GetTransform();

	return glm::lookAt(transform.Location, transform.Location + transform.ForwardVector, transform.UpVector);
}
