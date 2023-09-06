/*********************************************************************
 *   File: Transform.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: September 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Core/Transform.hpp"
#include <Math.hpp>


FVector AFTransform::WorldUpVector{0.f, 1.f, 0.f };
FVector AFTransform::WorldForwardVector{0.f, 0.f, -1.f };
FVector AFTransform::WorldRightVector{-1.f, 0.f, 0.f };

//FQuaternion AFTransform::LookAt(FVector direction, FVector upVector)
//{
//	static const FVector z(0.0f, 0.0f, -1.0f);
//	static const FVector y(0.0f, 1.0f, 0.0f);
//	direction = normalize(direction);
//	FVector right = glm::cross(direction, upVector);
//	FVector actual_up = glm::cross(right, direction);
//	FQuaternion look_transform = Rotate(direction, z);
//	//FQuaternion up_transform = Rotate(look_transform * actual_up, EAxis::YZ);
//	//return up_transform * look_transform;
//
//	return FQuaternion();
//}
//
//FQuaternion AFTransform::Rotate(FVector from, FVector to)
//{
//	/*from = normalize(from);
//	to = normalize(to);
//
//	float cos_angle = dot(from, to);
//	if (abs(cos_angle) > 0.9999f)
//	{
//		if (cos_angle > 0.9999f)
//			return FQuaternion(1.0f, 0.0f, 0.0f, 0.0f);
//		else
//		{
//			FVector rotation = cross(vec3(1.0f, 0.0f, 0.0f), from);
//			if (dot(rotation, rotation) > 0.001f)
//				rotation = normalize(rotation);
//			else
//				rotation = normalize(cross(vec3(0.0f, 1.0f, 0.0f), from));
//			return quat(0.0f, rotation);
//		}
//	}
//
//	FVector rotation = normalize(cross(from, to));
//	FVector half_vector = normalize(from + to);
//	float cos_half_range = clamp(dot(half_vector, from), 0.0f, 1.0f);
//	float sin_half_angle = sqrtf(1.0f - cos_half_range * cos_half_range);
//	return quat(cos_half_range, rotation * sin_half_angle);*/
//
//	return FQuaternion();
//}
//
//FQuaternion AFTransform::Rotate(FVector from, FVector to, EAxis axis)
//{
//	float x = (axis == EAxis::X || axis == EAxis::XY || axis == EAxis::XZ || axis == EAxis::XYZ) ? 1.f : 0.f;
//	float y = (axis == EAxis::Y || axis == EAxis::XY || axis == EAxis::YZ || axis == EAxis::XYZ) ? 1.f : 0.f;
//	float z = (axis == EAxis::Z || axis == EAxis::XZ || axis == EAxis::YZ || axis == EAxis::XYZ) ? 1.f : 0.f;
//	FVector axisVector = glm::normalize(FVector{ x, y, z });
//	from = glm::normalize(from);
//	to = glm::normalize(to);
//
//	//if(FMath::Dot(to, from))
//
//	return FQuaternion();
//}
