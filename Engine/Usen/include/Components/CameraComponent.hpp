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

class UCameraComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()

public:
	void Construct() override;

	void SetYaw(float value);
	void SetPitch(float value);
	void SetRoll(float value);

	float GetFieldOfView() const { return Fov; }
	float GetNear() const { return Near; };
	float GetFar() const { return Far; };
protected:
	void Serialize(SeriFile& otherOut) override;

	void UpdateView();

private:
	float Near{ 0.0001f };
	float Far{ 100000.f };
	float Fov{ 45.f };

	float Yaw{ 0.f };
	float Pitch{ 0.f };
	float Roll{ 0.f };

	FVector YawAxis{ 0.0f, 1.0f, 0.0f };
	FVector PitchAxis{ 1.0f, 0.0f, 0.0f };
	FVector RollAxis{ 0.0f, 0.0f, 1.0f };

	FVector ViewPoint{ 0.0f, 0.0f, 0.0f };
};

#endif // !US_CAMERA_COMPONENT_HPP