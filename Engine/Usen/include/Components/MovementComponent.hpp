/*********************************************************************
 *   File: MovementComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_MOVEMENT_COMPONENT_HPP
#define	US_MOVEMENT_COMPONENT_HPP


#include "Components/Component.hpp"
#include "MovementComponent-generated.hpp"

//enum class EAxis : uint8
//{
//	X,
//	Y,
//	Z,
//};

class UMovementComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()
public:
	float Speed = 10.f;
	float JumpScale = 100.f;
	bool bUseGravity = true;

	void Construct() override;

	void AddForwardMovement(float scaleMovement);
	void AddRightMovement(float scaleMovement);

	void Update(float deltaTime) override;
};

#endif // !US_MOVEMENT_COMPONENT_HPP