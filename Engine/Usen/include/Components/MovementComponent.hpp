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

class UMovementComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()
public:
	float Speed = 10.f;

	void AddForwardMovement(float scaleMovement);
	void AddRightMovement(float scaleMovement);
};

#endif // !US_MOVEMENT_COMPONENT_HPP