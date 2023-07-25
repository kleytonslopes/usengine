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
	explicit UCameraComponent();
	~UCameraComponent() final;

protected:
	void Serialize(SeriFile& otherOut) override;

private:
	float Near{ 0.001f };
	float Far{ 100000.f };
	float Fov{ 45.f };

	float Yaw{ 0.f };
	float Pitch{ 0.f };
	float Roll{ 0.f };

	FVector YawAxis{ 0.0f, 1.0f, 0.0f };
	FVector PitchAxis{ 1.0f, 0.0f, 0.0f };
	FVector RollAxis{ 0.0f, 0.0f, 1.0f };
};

#endif // !US_CAMERA_COMPONENT_HPP