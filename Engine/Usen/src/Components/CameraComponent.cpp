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
#include <Core/Rotator.hpp>
#include <Core/Math.hpp>
#include "Presentation/Window.hpp"
#include "Runtime/Application.hpp"

DEFAULT_BODY(UCameraComponent);

void UCameraComponent::Construct()
{
	Super::Construct();
	GetWindow()->OnWindowResizedEvent.Add(this, &This::OnWindowResizedEvent);

	AspectRatio = GetWindow()->GetWidth() / GetWindow()->GetHeight();

	SetLocation(FVector{ 0.f, 0.f, 0.f });
}

void UCameraComponent::PostConstruct()
{
	Super::PostConstruct();

	/* Initialize camera View */
	SetForwardVector(AFTransform::WorldForwardVector);
	CameraDirection = glm::normalize(CameraTrasnsform.GetLocation() - CameraTrasnsform.GetForwardVector());

	SetUpVector(glm::cross(CameraDirection, CameraTrasnsform.GetRightVector()));

	LastX = GetWindow()->GetWidth() / 2.f;
	LastY = GetWindow()->GetHeight() / 2.f;
	AddMovementYaw(90.f);
	FVector location = CameraTrasnsform.GetLocation();
	location.y = 3.f;
	SetLocation(location);
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

void UCameraComponent::SetLocation(const FVector& location)
{
	CameraTrasnsform.SetLocation(location);
	//if (Parent)
	//{
	//	AActor* aParent = Cast<AActor*>(Parent);
	//	if(aParent)
	//	{
	//		aParent->SetLocation(CameraTrasnsform.GetLocation());
	//	}
	//}
}

void UCameraComponent::SetRotation(const FQuaternion& quaternion)
{
	//Rotation = quaternion;
}

void UCameraComponent::SetForwardVector(const FVector& vector)
{
	CameraTrasnsform.SetForwardVector(vector);
	if (Parent)
	{
		AActor* aParent = Cast<AActor*>(Parent);
		if (aParent)
		{
			aParent->SetForwardVector(CameraTrasnsform.GetForwardVector());
		}
	}
}

void UCameraComponent::SetUpVector(const FVector& vector)
{
	CameraTrasnsform.SetUpVector(vector);
	if (Parent)
	{
		AActor* aParent = Cast<AActor*>(Parent);
		if (aParent)
		{
			aParent->SetUpVector(CameraTrasnsform.GetUpVector());
		}
	}
}

void UCameraComponent::LookAt(const FVector& eye, const FVector& target, const FVector& upVector)
{

	//Rotation = AFTransform::LookAt()
}

FMatrix4 UCameraComponent::GetViewProjection()
{
	FMatrix4 view = glm::lookAt(CameraTrasnsform.GetLocation(), CameraTrasnsform.GetLocation() + ViewPoint, CameraTrasnsform.GetUpVector());
	FMatrix4 projection = glm::perspective(Fov, AspectRatio, Near, Far);
	return view;
}

FMatrix4 UCameraComponent::GetView()
{
	return glm::lookAt(CameraTrasnsform.GetLocation(), CameraTrasnsform.GetLocation() + CameraTrasnsform.GetForwardVector(), CameraTrasnsform.GetUpVector());
}

void UCameraComponent::AddMovementForward(FVector direction)
{
	SetLocation(direction);
	//CameraTrasnsform.SetLocation(direction);
}

void UCameraComponent::AddMovementRight(FVector direction)
{
	SetLocation(direction);
	//CameraTrasnsform.SetLocation(direction);
}

void UCameraComponent::AddMovementYaw(float value)
{
	Yaw -= value;
}

void UCameraComponent::AddMovementPitch(float value)
{
	Pitch -= value;

	if (Pitch > 89.f)
		Pitch = 89.f;
	if (Pitch < -89.f)
		Pitch = -89.f;
}

void UCameraComponent::AddMouseMovement(float deltaTime, int xrel, int yrel)
{
	Yaw -= xrel * Sensitivity * deltaTime;
	Pitch -= yrel * Sensitivity * deltaTime;

	if (Pitch > 89.f)
		Pitch = 89.f;
	if (Pitch < -89.f)
		Pitch = -89.f;

	float yRadians = glm::radians(Yaw);
	float pRadians = glm::radians(Pitch);

	glm::vec3 front;

	front.x = -sin(yRadians) * cos(pRadians);
	front.y = sin(pRadians);
	front.z = -cos(yRadians) * cos(pRadians);
	SetForwardVector(glm::normalize(front));
	
	FVector right = glm::normalize(glm::cross(CameraTrasnsform.GetForwardVector(), AFTransform::WorldUpVector));
	CameraTrasnsform.SetUpVector(glm::normalize(glm::cross(right, CameraTrasnsform.GetForwardVector())));

	//ViewPoint.x = targ.x;
	//ViewPoint.y = targ.y;
	//ViewPoint.z = targ.z;



	//CameraTrasnsform.SetForwardVector(glm::normalize(front));
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
	//Key(otherOut, "yawAxis", YawAxis);
	//Key(otherOut, "pitchAxis", PitchAxis);
	//Key(otherOut, "rollAxis", RollAxis);

	EndSection(otherOut);
}

void UCameraComponent::UpdateView()
{

	double x = ViewPoint.x;//1.0; // Initial X component
	double y = ViewPoint.y; // Initial Y component
	double z = ViewPoint.z; // Initial Z component

	double angleX = glm::radians(Roll);//45.0 * M_PI / 180.0; // Angle in radians for rotation around X-axis
	double angleY = glm::radians(Yaw);//30.0 * M_PI / 180.0; // Angle in radians for rotation around Y-axis
	double angleZ = glm::radians(Pitch);//60.0 * M_PI / 180.0; // Angle in radians for rotation around Z-axis

	//FRotator rotator{ 1.f, 2.f, 3.f };

	double sinx = std::sin(angleX / 2.0);
	double siny = std::sin(angleY / 2.0);
	double sinz = std::sin(angleZ / 2.0);

	FRotator rotationQuaternionX(sinx, 0.0, 0.0, std::cos(angleX / 2.0));
	FRotator rotationQuaternionY(0.0, siny, 0.0, std::cos(angleY / 2.0));
	FRotator rotationQuaternionZ(0.0, 0.0, sinz, std::cos(angleZ / 2.0));

	rotationQuaternionX = FRotator::Normalize(rotationQuaternionX);
	rotationQuaternionY = FRotator::Normalize(rotationQuaternionY);
	rotationQuaternionZ = FRotator::Normalize(rotationQuaternionZ);


	FRotator::Rotate(x, y, z, rotationQuaternionX);
	FRotator::Rotate(x, y, z, rotationQuaternionY);
	FRotator::Rotate(x, y, z, rotationQuaternionZ);
	ViewPoint.x = x;//rotationQuaternionX.GetX();
	ViewPoint.y = y;//rotationQuaternionY.GetY();
	ViewPoint.z = z;//rotationQuaternionZ.GetZ();

	//if (Parent)
	//{
	//	AActor* aParent = Cast<AActor*>(Parent);
	//	if (aParent)
	//		aParent->SetForwardVector(ViewPoint);
	//}



	//if (Pitch > 89.f)
	//	Pitch = 89.f;
	//if (Pitch < -89.f)
	//	Pitch = -89.f;

	/*
	float yallRadians = glm::radians(Yaw);
	float pitchRadians = glm::radians(Pitch);
	//float rollRadians = glm::radians(Roll);

	FVector targetView;

	targetView.x = -sin(yallRadians) * cos(pitchRadians);
	targetView.y = sin(pitchRadians);
	targetView.z = -cos(yallRadians) * cos(pitchRadians);
	targetView = glm::normalize(targetView);

	ViewPoint.x = targetView.x;
	ViewPoint.y = targetView.y;
	ViewPoint.z = targetView.z;

	if (Parent)
	{
		AActor* aParent = Cast<AActor*>(Parent);
		if(aParent)
			aParent->SetForwardVector(glm::normalize(ViewPoint));
	}
	*/

	/*
	FMatrix4 matrix = FMatrix4{ 1.f };

	matrix = glm::translate(matrix, GetLocation());
	matrix = glm::rotate(matrix, glm::radians(Pitch), FVector{ 1.f, 0.f, 0.f });
	matrix = glm::rotate(matrix, glm::radians(Yaw), FVector{ 0.f, 1.f, 0.f });
	matrix = glm::rotate(matrix, glm::radians(Roll), FVector{ 0.f, 0.f, 1.f });

	FMatrix3 mat3 = matrix;
	//ViewPoint = mat3;
	ViewPoint.y = matrix[0][0];
	ViewPoint.y = matrix[1][1];
	ViewPoint.z = matrix[2][2];

	if (Parent)
	{
		AActor* aParent = Cast<AActor*>(Parent);
		if (aParent)
			aParent->SetForwardVector(ViewPoint);
	}
	*/


	//ViewPoint.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	//ViewPoint.y = sin(glm::radians(Pitch));
	//ViewPoint.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	//ViewPoint = glm::normalize(ViewPoint);

	/*
	FVector front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front = glm::normalize(front);

	// Calculate the new right and up vectors
	FVector right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	FVector up = glm::normalize(glm::cross(right, front));

	if (Parent)
	{
		AActor* aParent = Cast<AActor*>(Parent);
		if (aParent)
			aParent->SetForwardVector(glm::cross(right, front));
	}
	*/


	//FMatrix4 rotM = glm::mat4(1.0f);
	//FMatrix4 transM;

	//rotM = glm::rotate(rotM, glm::radians(Rotation.x * (flipY ? -1.0f : 1.0f)), glm::vec3(1.0f, 0.0f, 0.0f));
	//rotM = glm::rotate(rotM, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	//rotM = glm::rotate(rotM, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	//glm::vec3 translation = Position;
	//if (flipY) {
	//	translation.y *= -1.0f;
	//}
	//transM = glm::translate(glm::mat4(1.0f), translation);

	////if (type == CameraType::FirstPerson)
	////{
	//matrices.view = rotM * transM;
	////}
	////else
	////{
	////	matrices.view = transM * rotM;
	////}

	//ViewPosition = glm::vec4(Position, 0.0f) * glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);

	//updated = true;
/*
	double yaw = glm::radians(Yaw);
	double pitch = glm::radians(Pitch);
	double roll = glm::radians(Roll);

	FQuaternion quatPitch{ pitch , 1.0, 0.0 , 0.0 };
	FQuaternion quatYaw{ yaw , 0.0, 1.0 , 0.0 };
	FQuaternion quatRoll{ roll , 0.0, 0.0 , 1.0 };

	FVector3 vec3{ 1.0, 1.0, 0.0 };

	FVector3 rotatedvec = quatPitch.Rotate(vec3);
	rotatedvec = quatYaw.Rotate(rotatedvec);
	rotatedvec = quatRoll.Rotate(rotatedvec);
	if (Parent)
	{
		AActor* aParent = Cast<AActor*>(Parent);
		if (aParent)
			aParent->SetForwardVector(FVector{ rotatedvec.X, rotatedvec.Y, rotatedvec.Z });
	}
	*/
}

void UCameraComponent::OnWindowResizedEvent(uint32 width, uint32 height)
{
	if (width <= 0)	width = 128;
	if (height <= 0) height = 128;

	AspectRatio = GetWindow()->GetWidth() / GetWindow()->GetHeight();
}
