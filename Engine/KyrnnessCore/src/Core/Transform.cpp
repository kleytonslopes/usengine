/*********************************************************************
 *   File: Transform.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: September 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "Core/Transform.hpp"

Vector3 Transform::DefaultUpVector{0.0, 1.0, 0.0 };
Vector3 Transform::DefaultForwardVector{0.0, 0.0, 1.0 };
Vector3 Transform::DefaultScale{1.0, 1.0, 1.0 };
FRotator Transform::DefaultRotation{0.0, 0.0, 0.0 };
Location Transform::ZeroLocation{0.0, 0.0, 0.0 };

Location Transform::GetLocation()
{
	return mLocation;
}

Location Transform::GetOrigin()
{
	return mOrigin;
}

Location Transform::GetRelativeLocation()
{
	return mLocation + mOrigin;
}

FRotator Transform::GetRotation()
{
	return mRotation;
}

Vector3 Transform::GetScale()
{
	return mScale;
}

Vector3 Transform::GetUpVector()
{
	return mUpVector;
}

Vector3 Transform::GetForwardVector()
{
	return mForwardVector;
}

Vector3 Transform::GetRightVector()
{
	return Vector3::Normalize(Vector3::Cross(mUpVector, GetDirection()));
}

Vector3 Transform::GetDirection()
{
	return Vector3::Normalize(mLocation - mForwardVector);
}
