/*********************************************************************
 *   File: Transform.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: September 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef KNC_TRANSFORM_HPP
#define	KNC_TRANSFORM_HPP

#include "Core/Vectors/Vector3.hpp"
#include "Location.hpp"
#include "Rotator.hpp"

class KN_API Transform
{
	using T = double;
public:
	Transform() = default;

	~Transform() = default;

	Transform& operator=(const Transform& right) = default;
	
	inline bool operator==(const Transform& right) const
	{
		return (mLocation == right.mLocation
			 && mOrigin == right.mOrigin
			 && mScale == right.mScale);
	}
	inline bool operator!=(const Transform& right) const
	{
		return (mLocation != right.mLocation
			|| mOrigin != right.mOrigin
			|| mScale != right.mScale);
	}

	void SetLocation(const Location& location) { mLocation = location; };
	void SetOrigin(const Location& origin) { mOrigin = origin; };
	void SetScale(const Vector3& scale) { mScale = scale; };
	void SetUpVector(const Vector3& upVector) { mUpVector = upVector; };
	void SetForwardVector(const Vector3& forwardVector) { mForwardVector = forwardVector; };
	void SetRotation(const FRotator& rotation) { mRotation = rotation; }

	Location GetLocation();
	Location GetOrigin();
	Location GetRelativeLocation();
	FRotator GetRotation();
	Vector3 GetScale();
	Vector3 GetUpVector();
	Vector3 GetForwardVector();
	Vector3 GetRightVector();
	Vector3 GetDirection();

	static Vector3 DefaultUpVector;
	static Vector3 DefaultForwardVector;
	static Vector3 DefaultScale;
	static FRotator DefaultRotation;
	static Location ZeroLocation;

private:
	Location mLocation{ Transform::ZeroLocation };
	Location mOrigin{ Transform::ZeroLocation };
	FRotator mRotation{ Transform::DefaultRotation };
	Vector3 mScale{ Transform::DefaultScale };
	Vector3 mUpVector{ Transform::DefaultUpVector };
	Vector3 mForwardVector{ Transform::DefaultForwardVector };
};

#endif // !KNC_LOCATION_HPP