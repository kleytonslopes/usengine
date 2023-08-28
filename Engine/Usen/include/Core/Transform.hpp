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

class FTransform
{
public:
	FVector& GetLocation() { return Location; }
	FVector& GetOrigin() { return Origin; }
	FVector& GetRotation() { return Rotation; }
	FVector& GetScale() { return Scale; }
	FVector& GetUpVector() { return UpVector; }
	FVector& GetForwardVector() { return ForwardVector; }

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

private:
	FVector Location{ 0.f, 0.f, 0.f };
	FVector Origin{ 0.f, 0.f, 0.f };
	FVector Rotation{ 0.f, 0.f, 0.f };
	FVector Scale{ 1.f, 1.f, 1.f };
	FVector UpVector{ 0.f, 1.f, 0.f };
	FVector ForwardVector{ 0.f, 0.f, -1.f };
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





