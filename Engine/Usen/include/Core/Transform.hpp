/*********************************************************************
 *   File: Transform.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef US_TRANSFORM_HPP
#define	US_TRANSFORM_HPP

#include "Core/CommonTypes.hpp"
#include "Core/Vector.hpp"
#include "Core/Axis.hpp"

class FTransform
{
public:
	FVector& GetLocation() { return Location; }
	FVector& GetWorldLocation() { return Location + Origin; }
	FVector& GetOrigin() { return Origin; }
	FVector& GetRotation() { return Rotation; }
	FVector& GetScale() { return Scale; }
	FVector& GetUpVector() { return UpVector; }
	FVector& GetForwardVector() { return ForwardVector; }
	FVector GetRightVector()
	{
		return glm::normalize(glm::cross(UpVector, ForwardVector));
	}
	FVector GetDirection()
	{
		return glm::normalize(Location - ForwardVector);
	}

	void SetLocation(const FVector& vector)
	{
		Location = vector;
	}
	void SetOrigin(const FVector& vector)
	{
		Origin = vector;
	}
	void SetRotation(const FVector& vector)
	{
		Rotation = vector;
	}
	void SetScale(const FVector& vector)
	{
		Scale = vector;
	}
	void SetUpVector(const FVector& vector)
	{
		UpVector = vector;
	}
	void SetForwardVector(const FVector& vector)
	{
		ForwardVector = vector;
	}

	static FVector ZeroVector;
	static FVector WorldUpVector;
	static FVector WorldForwardVector;
	static FVector WorldRightVector;

private:
	FVector Location{ 0.f, 0.f, 0.f };
	FVector Origin{ 0.f, 0.f, 0.f };
	FVector Rotation{ 0.f, 0.f, 0.f };
	FVector Scale{ 1.f, 1.f, 1.f };
	FVector UpVector = FTransform::WorldUpVector;//{ 0.f, 0.f, 1.f };       /// Y+
	FVector ForwardVector = FTransform::WorldForwardVector;//{ 1.f, 0.f, 0.f }; /// Z-
};

#endif // !US_TRANSFORM_HPP


/*


	 (Y+) up
	  |
	  |
	  |
	  |
	  O--------- (X+) left
	 /
	/
   /
 (Z-) forward


*/





