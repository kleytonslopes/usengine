/*********************************************************************
 *   File: PhysicsShapeInitialize.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_PHYSICS_SHAPE_INITIALIZE_HPP
#define	US_PHYSICS_SHAPE_INITIALIZE_HPP

#include "Core/MinimalCore.hpp"

enum class EShapeForm : uint8
{
	ESF_None,
	ESF_Box,
	ESF_Sphere,
	ESF_Capsule,
};

class FPhysicsShapeInitialize
{
	
public:
	EShapeForm Shape = EShapeForm::ESF_Box;

	float Radius = 1.f;
	float HalfHeight = 1.f;

	float HalfHeightX = 1.f;
	float HalfHeightY = 1.f;
	float HalfHeightZ = 1.f;

	float Mass = 10.f;

	FPhysicsShapeInitialize& operator= (const FPhysicsShapeInitialize& other)
	{
		this->Radius = other.Radius;
		this->HalfHeight = other.HalfHeight;
		this->HalfHeightX = other.HalfHeightX;
		this->HalfHeightY = other.HalfHeightY;
		this->HalfHeightZ = other.HalfHeightZ;
		this->Mass = other.Mass;

		return *this;
	}

	void InitializeBox(const float& halfHeightX, const float& halfHeightY, const float& halfHeightZ)
	{
		Shape = EShapeForm::ESF_Box;

		HalfHeightX = halfHeightX;
		HalfHeightY = halfHeightY;
		HalfHeightZ = halfHeightZ;
	}
};

#endif // !US_PHYSICS_SHAPE_INITIALIZE_HPP