/*********************************************************************
 *   File: CameraComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Components/CameraComponent.hpp"
#include "Actors/Actor.hpp"

DEFAULT_BODY(UCameraComponent);

void UCameraComponent::Construct()
{
	Super::Construct();
}

void UCameraComponent::SetYaw(float value)
{
	Yaw = value;

	UpdateView();
}

void UCameraComponent::SetPitch(float value)
{
	Pitch = value;
	UpdateView();
}

void UCameraComponent::SetRoll(float value)
{
	Roll = value;
	UpdateView();
}

void UCameraComponent::SetFieldOfView(float fov)
{
	Fov = fov;
}

void UCameraComponent::Serialize(SeriFile& otherOut)
{
	BeginComponentSection(otherOut, Identity);

	Key(otherOut, "near", Near);
	Key(otherOut, "far", Far);
	Key(otherOut, "fov", Fov);
	Key(otherOut, "yaw", Yaw);
	Key(otherOut, "pitch", Pitch);
	Key(otherOut, "roll", Roll);
	Key(otherOut, "yawAxis", YawAxis);
	Key(otherOut, "pitchAxis", PitchAxis);
	Key(otherOut, "rollAxis", RollAxis);

	EndSection(otherOut);
}

void UCameraComponent::UpdateView()
{
	float yallRadians = glm::radians(Yaw);
	float pitchRadians = glm::radians(Pitch);

	FVector targetView;

	targetView.x = -sin(yallRadians) * cos(pitchRadians);
	targetView.y = sin(pitchRadians);
	targetView.z = -cos(yallRadians) * cos(pitchRadians);

	ViewPoint.x = targetView.x;
	ViewPoint.y = targetView.y;
	ViewPoint.z = targetView.z;

	if (Parent)
	{
		AActor* aParent = Cast<AActor*>(Parent);
		if(aParent)
			aParent->SetForwardVector(ViewPoint);
	}
}
