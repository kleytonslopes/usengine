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

void ACamera::Construct()
{
	Super::Construct();

	bCanTick = false;

	CameraComponent = AddComponent<UCameraComponent>();
	//cameraComponent->SetOwner(Owner);
	//cameraComponent->SetParent(this);
}

FMatrix4 ACamera::GetView()
{
	const FTransform& transform = GetTransform();

	return glm::lookAt(transform.Location, transform.Location + transform.ForwardVector, transform.UpVector);
}

void ACamera::SetRotation(FVector& vector)
{
	CameraComponent->SetPitch(vector.x);
	CameraComponent->SetRoll(vector.y);
	CameraComponent->SetYaw(vector.z);
}

float ACamera::GetFieldOfView() const
{
	return CameraComponent->GetFieldOfView();
}

float ACamera::GetNear() const
{
	return CameraComponent->GetNear();
}

float ACamera::GetFar() const
{
	return CameraComponent->GetFar();
}
