/*********************************************************************
 *   File: CameraComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CAMERA_COMPONENT_HPP
#define	US_CAMERA_COMPONENT_HPP


#include "Components/Component.hpp"
#include "CameraComponent-generated.hpp"
#include "Core/Quaternion.hpp"

class UCameraComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()

public:
	FTransform CameraTrasnsform{};

	void Construct() override;
	void PostConstruct() override;

	void SetYaw(float value);
	void SetPitch(float value);
	void SetRoll(float value);
	void SetFieldOfView(float fov);

	void SetLocation(const FVector& location);
	void SetRotation(const FQuaternion& quaternion);
	void SetForwardVector(const FVector& vector);
	void SetUpVector(const FVector& vector);
	void LookAt(const FVector& eye, const FVector& target, const FVector& upVector);

	float GetFieldOfView() const { return Fov; }
	float GetNear() const { return Near; };
	float GetFar() const { return Far; };
	float GetPitch() const { return Pitch; };
	float GetYaw() const { return Yaw; };
	float GetRoll() const { return Roll; };
	FMatrix4 GetViewProjection();
	FMatrix4 GetView();

	void AddMovementForward(FVector direction);
	void AddMovementRight(FVector direction);
	void AddMovementYaw(float value);
	void AddMovementPitch(float value);
	void AddMouseMovement(float deltaTime, int xrel, int yrel);
protected:
	void Serialize(SeriFile& otherOut) override;

	void UpdateView();
	
	void OnWindowResizedEvent(uint32 width, uint32 height);

private:
	//AFTransform CameraTrasnsform{};
	float Near{ 0.0001f };
	float Far{ 100000.f };
	float Fov{ 45.f };
	float AspectRatio{ 0.f };
	float Sensitivity{ 2.f };

	float Pitch{ 0.f };
	float Yaw{ 90.0f };
	float Roll{ 0.f };

	float AngleH;
	float AngleV;



	////--
	//FQuaternion Rotator{};
	//FVector Position{ 0.0f, 0.0f, 3.0f };
	////--

	//FVector YawAxis{ 0.0f, 1.0f, 0.0f };
	//FVector PitchAxis{ 1.0f, 0.0f, 0.0f };
	//FVector RollAxis{ 0.0f, 0.0f, 1.0f };

	FVector ViewPoint{ 0.0f, 0.0f, 0.0f };
	
	FVector CameraDirection;
	float LastX;
	float LastY;
};

#endif // !US_CAMERA_COMPONENT_HPP