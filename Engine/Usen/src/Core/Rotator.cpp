/*********************************************************************
 *   File: Rotator.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Core/Rotator.hpp"

AFRotator::AFRotator(/*const FVector& vector, float a*/)
{
	/*a = a / 360 * (float)M_PI * 2;

	W = cos(a / 2);

	X = vector.x * sin(a / 2);
	Y = vector.y * sin(a / 2);
	Z = vector.z * sin(a / 2);*/
}

FVector AFRotator::Rotate()
{
	float a1 = 1.f;
	float a2 = 0.f;
	float a3 = 0.f;

	float b1 = 0.f;
	float b2 = 1.f;
	float b3 = 0.f;

	float c1 = 0.f;
	float c2 = 0.f;
	float c3 = 1.f;

	/* x axis
		1   0   0
		0  cos -sin
		0  sin  cos
	*/

	/* y axis
	cos  0  sin
	 0   1   0
   -sin  0  cos
    */

	/* z axis
        cos  -sin  0
        sin   cos  0
         0     0   1
    */

	return FVector();
}
