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
#include "Presentation/Window.hpp"

DEFAULT_BODY(ACamera);

void ACamera::Construct()
{
	Super::Construct();

	bCanTick = false;

	CameraComponent = AddComponent<UCameraComponent>();
	UWindow* window = GetWindow();
	ViewSize.x = window->GetWidth();
	ViewSize.y = window->GetHeight();

	//cameraComponent->SetOwner(Owner);
	//cameraComponent->SetParent(this);
}

FMatrix4 ACamera::GetView()
{
	FTransform& transform = GetTransform();

	return glm::lookAt(transform.GetLocation(), transform.GetLocation() + transform.GetForwardVector(), transform.GetUpVector());
}

void ACamera::SetRotation(FVector& vector)
{
	Super::SetRotation(vector);
	CameraComponent->SetPitch(vector.x);
	CameraComponent->SetRoll(vector.y);
	CameraComponent->SetYaw(vector.z);
}

void ACamera::SetViewSize(int width, int height)
{
	ViewSize.x = width;
	ViewSize.y = height;
}

void ACamera::SetFieldOfView(float fov)
{
	CameraComponent->SetFieldOfView(fov);
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

float ACamera::GetAspectRatio()
{
	
	return (float)ViewSize.x / (float)ViewSize.y;
}
