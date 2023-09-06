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
#include <Rotator.hpp>
#include <Math.hpp>
#include "Presentation/Window.hpp"
#include "Runtime/Application.hpp"

DEFAULT_BODY(UCameraComponent);

void UCameraComponent::Construct()
{
	Super::Construct();
	GetWindow()->OnWindowResizedEvent.Add(this, &This::OnWindowResizedEvent);

	AspectRatio = GetWindow()->GetWidth() / GetWindow()->GetHeight();
	//Fov = FMath::Radians(Fov);
}

void UCameraComponent::PostConstruct()
{
	Super::PostConstruct();

	FVector target(ViewPoint.x, 0.f, ViewPoint.z);

	float angle = FMath::Degrees(asin(abs(target.z)));

	if (target.z >= 0.f)
	{
		if (target.x >= 0.0f)
		{
			AngleH = 360.0f - angle;
		}
		else
		{
			AngleH = 180.0f + angle;
		}
	}
	else
	{
		if (target.x >= 0.0f)
		{
			AngleH = angle;
		}
		else
		{
			AngleH = 180.0f - angle;
		}
	}

	AngleV = -FMath::Degrees(asin(target.y));

}

void UCameraComponent::SetYaw(float value)
{
	ULOG_Trace(FText::Format("Yaw: %f", Yaw));
	Yaw = value;
	UpdateView();
}

void UCameraComponent::SetPitch(float value)
{
	ULOG_Trace(FText::Format("Pitch: %f", Pitch));
	Pitch = value;
	//if (Pitch > 0.f)
	//	Pitch = 0.f;
	//if (Pitch < -179.f)
	//	Pitch = -179.f;
	//if (Pitch > 89.f)
	//	Pitch = 89.f;
	//if (Pitch < -89.f)
	//	Pitch = -89.f;

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
	Position = location;
}

void UCameraComponent::SetRotation(const FQuaternion& quaternion)
{
	//Rotation = quaternion;
}

void UCameraComponent::LookAt(const FVector& eye, const FVector& target, const FVector& upVector)
{
	Position = eye;
	//Rotation = AFTransform::LookAt()
}

FMatrix4 UCameraComponent::GetViewProjection()
{
	FMatrix4 view = glm::lookAt(GetLocation(), GetLocation() + GetForwardVector(), GetUpVector());
	FMatrix4 projection = glm::perspective(Fov, AspectRatio, Near, Far);
	return view * projection;
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
	/*
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

	if (Parent)
	{
		AActor* aParent = Cast<AActor*>(Parent);
		if (aParent)
			aParent->SetForwardVector(ViewPoint);
	}
	*/

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

	double yaw = glm::radians(Yaw);
	double pitch = glm::radians(Pitch);
	double roll = glm::radians(Roll);

	FQuaternion quatPitch{ pitch , 1.0, 0.0 , 0.0 };
	FQuaternion quatYaw{ yaw , 0.0, 1.0 , 0.0 };
	FQuaternion quatRoll{ roll , 0.0, 0.0 , 1.0 };

	FVector3 vec3{ 1.0, 1.0, 0.0 };
	//if (Parent)
	//{
	//	AActor* aParent = Cast<AActor*>(Parent);
	//	if (aParent)
	//	{

	//		FVector fwrd = aParent->GetForwardVector();
	//		vec3.X = fwrd.x;
	//		vec3.Y = fwrd.y;
	//		vec3.Z = fwrd.z;
	//	}
	//}

	FVector3 rotatedvec = quatPitch.Rotate(vec3);
	rotatedvec = quatYaw.Rotate(rotatedvec);
	rotatedvec = quatRoll.Rotate(rotatedvec);
	if (Parent)
	{
		AActor* aParent = Cast<AActor*>(Parent);
		if (aParent)
			aParent->SetForwardVector(FVector{ rotatedvec.X, rotatedvec.Y, rotatedvec.Z });
	}
}

void UCameraComponent::UpdatePitch(double& y, double& z, double angle)
{
	double cosA = cos(angle);
	double sinA = sin(angle);

	///double tempX = x;
	double tempY = y;
	double tempZ = z;

	y = cosA * tempY - sinA * tempZ;
	z = sinA * tempY + cosA * tempZ;
}

void UCameraComponent::UpdateYaw(double& x, double& z, double angle)
{
	double cosA = cos(angle);
	double sinA = sin(angle);

	double tempX = x;
	//double tempY = y;
	double tempZ = z;

	//if (axis == 'X' || axis == 'x') {
	//	y = cosA * tempY - sinA * tempZ;
	//	z = sinA * tempY + cosA * tempZ;
	//}
	//else if (axis == 'Y' || axis == 'y') {
	x = cosA * tempX + sinA * tempZ;
	z = -sinA * tempX + cosA * tempZ;
	//}
	//else if (axis == 'Z' || axis == 'z') {
	//	x = cosA * tempX - sinA * tempY;
	//	y = sinA * tempX + cosA * tempY;
	//}
	//else {
	//	//std::cerr << "Invalid axis specified." << std::endl;
	//}

	//ViewPoint.x = targetView.x;
	//ViewPoint.y = targetView.y;
	//ViewPoint.z = targetView.z;
}

void UCameraComponent::UpdateRoll(double angle)
{
}

void UCameraComponent::OnWindowResizedEvent(uint32 width, uint32 height)
{
	if (width <= 0)	width = 128;
	if (height <= 0) height = 128;

	AspectRatio = GetWindow()->GetWidth() / GetWindow()->GetHeight();
}
