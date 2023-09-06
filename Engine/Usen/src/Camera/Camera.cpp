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
	
	AFTransform& transform = GetTransform();

	return glm::lookAt(transform.GetLocation(), transform.GetLocation() + transform.GetForwardVector(), transform.GetUpVector());
}

void ACamera::SetRotation(FVector& vector)
{
	Super::SetRotation(vector);
	//CameraComponent->SetPitch(vector.x);
	//CameraComponent->SetYaw(vector.y);
	//CameraComponent->SetRoll(vector.z);
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

float ACamera::GetPitch() const
{
	if (CameraComponent)
		return CameraComponent->GetPitch();
	return 0.0f;
}

float ACamera::GetYaw() const
{
	if (CameraComponent)
		return CameraComponent->GetYaw();
	return 0.0f;
}

float ACamera::GetRoll() const
{
	if (CameraComponent)
		return CameraComponent->GetRoll();
	return 0.0f;
}

void ACamera::SetPitch(const float& value)
{
	if (CameraComponent)
		CameraComponent->SetPitch(value);
}

void ACamera::SetYaw(const float& value)
{
	if (CameraComponent)
		CameraComponent->SetYaw(value);
}

void ACamera::SetRoll(const float& value)
{
	if (CameraComponent)
		CameraComponent->SetRoll(value);
}

void ACamera::AddPitch(float& value)
{
	if (CameraComponent)
	{
		value += CameraComponent->GetPitch();
		CameraComponent->SetPitch(value);
	}
}

void ACamera::AddYaw(float& value)
{
	if (CameraComponent) 
	{
		value += CameraComponent->GetYaw();
		CameraComponent->SetYaw(value);
	}
}

void ACamera::AddRoll(float& value)
{
	if (CameraComponent) 
	{
		value += CameraComponent->GetRoll();
		CameraComponent->SetRoll(value);
	}
}
