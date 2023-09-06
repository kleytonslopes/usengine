/*********************************************************************
 *   File: Camera.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CAMERA_HPP
#define	US_CAMERA_HPP


#include "Actors/Actor.hpp"
#include "Camera-generated.hpp"

class UCameraComponent;

class ACamera : public AActor
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	FMatrix4 GetView();

	void SetRotation(FVector& vector) override;
	void SetViewSize(int width, int height);
	void SetFieldOfView(float fov);
	
	float GetFieldOfView() const;
	float GetNear() const;
	float GetFar() const;
	float GetAspectRatio();

	/// <summary>
	/// Get Pitch axis from CameraComponent
	/// </summary>
	/// <returns></returns>
	float GetPitch() const;
	/// <summary>
	/// Get Yaw axis from CameraComponent
	/// </summary>
	/// <returns></returns>
	float GetYaw() const;
	/// <summary>
	/// Get Roll axis from CameraComponent
	/// </summary>
	/// <returns></returns>
	float GetRoll() const;

	void SetPitch(const float& value);
	void SetYaw(const float& value);
	void SetRoll(const float& value);

	void AddPitch(float& value);
	void AddYaw(float& value);
	void AddRoll(float& value);
private:
	UCameraComponent* CameraComponent = nullptr;

	FVector2 ViewSize;
};

#endif // !US_CAMERA_HPP