/*********************************************************************
 *   File: Quaternion.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: September 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#include "Vector3.hpp"

class FQuaternion
{
	using T = double;
public:
	FQuaternion();
	FQuaternion(T w, T x, T y, T z);

	FQuaternion operator*(const FQuaternion& other) const;

	T GetW() const { return W; }
	T GetX() const { return X; }
	T GetY() const { return Y; }
	T GetZ() const { return Z; }

	T Magnitude() const;
	void Normalize();
	FQuaternion Conjugate() const;

	static FQuaternion FromAxisAngle(T angle, T axisX, T axisY, T axisZ);
	FVector3 Rotate(const FVector3& vector) const;

private:
	T W;
	T X;
	T Y;
	T Z;
};

