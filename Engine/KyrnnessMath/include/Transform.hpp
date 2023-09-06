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

#ifndef KNM_TRANSFORM_HPP
#define	KNM_TRANSFORM_HPP

#include "Vector3.hpp"
#include "Rotator.hpp"

class FTransform
{
public:
	static FVector3 AxisX;
	static FVector3 AxisY;
	static FVector3 AxisZ;
	static FVector3 WorldUpVector;
	static FVector3 WorldForwardVector;
	static FVector3 WorldRightVector;

	FVector3 Location = FVector3::ZeroVector();
	FVector3 Origin = FVector3::ZeroVector();
	FVector3 Scale{ 1.f, 1.f, 1.f };
	FVector3 UpVector{ 0.f, 1.f, 0.f };
	FVector3 ForwardVector{ 0.f, 0.f, -1.f };
	FRotator Rotation = FRotator::ZeroRotator();

    FTransform() = default;
    FTransform(FVector3 location);

	FTransform& operator=(const FTransform& right) = default;
	FTransform& operator+(const FTransform& right);
	FTransform& operator-(const FTransform& right);
	FTransform& operator*(const FTransform& right);
	FTransform& operator/(const FTransform& right);

	FTransform& operator+=(const FTransform& right);
	FTransform& operator-=(const FTransform& right);
	FTransform& operator*=(const FTransform& right);
	FTransform& operator/=(const FTransform& right);

	bool operator==(const FTransform& right) const;
	bool operator!=(const FTransform& right) const;

	FVector3& GetLocation() { return Location; }
	FVector3& GetWorldLocation() { return Location + Origin; }
	FVector3& GetOrigin() { return Origin; }
	FRotator& GetRotation() { return Rotation; }
	FVector3& GetScale() { return Scale; }
	FVector3& GetUpVector() { return UpVector; }
	FVector3& GetForwardVector() { return ForwardVector; }

	void SetLocation(const FVector3& vector);
	void SetOrigin(const FVector3& vector);
	void SetRotation(const FRotator& rotator);
	void SetScale(const FVector3& vector);
	void SetUpVector(const FVector3& vector);
	void SetForwardVector(const FVector3& vector);
};

#endif // !KNM_TRANSFORM_HPP

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
