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
#include "Components/BoxCollisionComponent.hpp"
#include "Presentation/Window.hpp"
#include "Runtime/Application.hpp"

DEFAULT_BODY(ACamera);

void ACamera::Construct()
{
	Super::Construct();

	bCanTick = false;

	CameraComponent = AddComponent<UCameraComponent>();
	//CollisionComponent = AddComponent<UBoxCollisionComponent>();

	//CollisionComponent->SetIsDynamic(false);

	UWindow* window = GetWindow();
	ViewSize.x = window->GetWidth();
	ViewSize.y = window->GetHeight();

	//cameraComponent->SetOwner(Owner);
	//cameraComponent->SetParent(this);
}

void ACamera::Initialize()
{
	Super::Initialize();

	if (CollisionComponent)
	{
		CollisionComponent->SetLocation(GetLocation());
	}
}

void ACamera::SetLocation(FVector& vector)
{
	Super::SetLocation(vector);

	if (CameraComponent)
	{
		CameraComponent->SetLocation(vector);
	}
}

FMatrix4 ACamera::GetView()
{
	return CameraComponent->GetView();
	//AFTransform& transform = GetTransform();
	//return glm::lookAt(transform.GetLocation(), transform.GetLocation() + transform.GetForwardVector(), transform.GetUpVector());
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

UCameraComponent* ACamera::GetCameraComponent()
{
	return CameraComponent;
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

void ACamera::AddPitch(float value)
{
	if (CameraComponent)
	{
		ULOG_Trace(FText::Format("Add Pitch: %f", value));
		value += CameraComponent->GetPitch() * GetApplication()->GetDeltaTime();
		CameraComponent->SetPitch(value);
	}
}

void ACamera::AddYaw(float value)
{
	if (CameraComponent) 
	{
		value += CameraComponent->GetYaw() * GetApplication()->GetDeltaTime();
		CameraComponent->SetYaw(value);
	}
}

void ACamera::AddRoll(float value)
{
	if (CameraComponent) 
	{
		value += CameraComponent->GetRoll() * GetApplication()->GetDeltaTime();
		CameraComponent->SetRoll(value);
	}
}

void ACamera::AddMouseMovement(float deltaTime, int xrel, int yrel)
{
	if (CameraComponent)
	{
		CameraComponent->AddMouseMovement(deltaTime, xrel, yrel);
	}
}

void ACamera::AddMovementForward(FVector direction)
{
	if (CameraComponent)
	{
		CameraComponent->AddMovementForward(direction);
	}
}
