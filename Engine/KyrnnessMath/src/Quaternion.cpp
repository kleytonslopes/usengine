/*********************************************************************
 *   File: Quaternion.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: September 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "Quaternion.hpp"
#include <math.h>

FQuaternion::FQuaternion()
	: W{ 1.0 }
	, X{ 0.0 }
	, Y{ 0.0 }
	, Z{ 0.0 }
{
}

FQuaternion::FQuaternion(T w, T x, T y, T z)
	: W{w}
	, X{x}
	, Y{y}
	, Z{z}
{
}

FQuaternion FQuaternion::operator*(const FQuaternion& other) const
{
	T newW = W * other.W - X * other.X - Y * other.Y - Z * other.Z;
	T newX = W * other.X + X * other.W + Y * other.Z - Z * other.Y;
	T newY = W * other.Y - X * other.Z + Y * other.W + Z * other.X;
	T newZ = W * other.Z + X * other.Y - Y * other.X + Z * other.W;

	return FQuaternion{ newW, newX, newY, newZ };
}

FQuaternion::T FQuaternion::Magnitude() const
{
	return sqrt(W * W 
	          + X * X
	          + Y * Y
	          + Z * Z);
}

void FQuaternion::Normalize()
{
	T magnitude = Magnitude();
	if (magnitude > 0.0)
	{
		W /= magnitude;
		X /= magnitude;
		Y /= magnitude;
		Z /= magnitude;
	}
}

FQuaternion FQuaternion::Conjugate() const
{
	return FQuaternion{ W, -X, -Y, -Z };
}

FQuaternion FQuaternion::FromAxisAngle(T angle, T axisX, T axisY, T axisZ)
{
	double halfAngle = angle / 2.0;
	double sinHalfAngle = sin(halfAngle);
	return FQuaternion(cos(halfAngle), axisX * sinHalfAngle, axisY * sinHalfAngle, axisZ * sinHalfAngle);
}

FVector3 FQuaternion::Rotate(const FVector3& vector) const
{
	FQuaternion v{ 0.0, vector.X, vector.Y, vector.Z };
	FQuaternion rotated = (*this) * v * this->Conjugate();
	return FVector3{ rotated.X, rotated.Y, rotated.Z };
}
