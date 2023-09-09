/*********************************************************************
 *   File: Transform.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: September 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "Transform.hpp"

Vector3 Transform::DefaultForwardVector{0.0, 0.0, -1.0};
Vector3 Transform::DefaultUpVector{0.0, 1.0, 0.0};
Vector3 Transform::DefaultScale{1.0, 1.0, 1.0};

Location Transform::ZeroLocation{0.0, 0.0, 0.0};

Vector3 Transform::GetRightVector()
{
	return Vector3::Normalize(Vector3::Cross(mUpVector, mForwardVector));
}
