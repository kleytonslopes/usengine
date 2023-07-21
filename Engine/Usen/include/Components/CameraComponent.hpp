/*********************************************************************
 *   File: CameraComponent.hpp
 *  Brief:
 *
 * Author: Kleyton
 *   Date: July 2023
 *
 * Copyright (c) 2023 Sunydark. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef US_CAMERA_COMPONENT_HPP
#define	US_CAMERA_COMPONENT_HPP

#include "Components/Interface/IComponent.hpp"

class UCameraComponent : public IComponent
{
	DEFAULT_BODY(IComponent);
public:
	UCameraComponent() = default;

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
