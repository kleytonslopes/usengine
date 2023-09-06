/*********************************************************************
 *   File: Vector.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "Vector3.hpp"
#include "Math.hpp"

FVector3::FVector3(T x, T y, T z)
	: X{ x }
	, Y{ y }
	, Z{ z }
{}

FVector3& FVector3::operator+(const FVector3& right)
{
	this->X += right.X;
	this->Y += right.Y;
	this->Z += right.Z;

	return *this;
}
FVector3& FVector3::operator-(const FVector3& right)
{
	this->X -= right.X;
	this->Y -= right.Y;
	this->Z -= right.Z;

	return *this;
}
FVector3& FVector3::operator*(const FVector3& right)
{
	this->X *= right.X;
	this->Y *= right.Y;
	this->Z *= right.Z;

	return *this;
}
FVector3& FVector3::operator/(const FVector3& right)
{
	this->X /= right.X;
	this->Y /= right.Y;
	this->Z /= right.Z;

	FMath::ResolveNaN(X);
	FMath::ResolveNaN(Y);
	FMath::ResolveNaN(Z);

	return *this;
}

FVector3& FVector3::operator+=(const FVector3& right)
{
	this->X += right.X;
	this->Y += right.Y;
	this->Z += right.Z;

	

	return *this;
}
FVector3& FVector3::operator-=(const FVector3& right)
{
	this->X -= right.X;
	this->Y -= right.Y;
	this->Z -= right.Z;

	return *this;
}
FVector3& FVector3::operator*=(const FVector3& right)
{
	this->X *= right.X;
	this->Y *= right.Y;
	this->Z *= right.Z;

	return *this;
}

FVector3& FVector3::operator/=(const FVector3& right)
{
	this->X /= right.X;
	this->Y /= right.Y;
	this->Z /= right.Z;

	FMath::ResolveNaN(X);
	FMath::ResolveNaN(Y);
	FMath::ResolveNaN(Z);

	return *this;
}

bool FVector3::operator==(const FVector3& right) const
{
	return X == right.X && Y == right.Y && Z == right.Z;
}
bool FVector3::operator!=(const FVector3& right) const
{
	return X != right.X || Y != right.Y || Z != right.Z;
}

void FVector3::SetX(const T& x)
{
	X = x;
}
void FVector3::SetY(const T& y)
{
	Y = y;
}
void FVector3::SetZ(const T& z)
{
	Z = z;
}

FVector3 FVector3::ZeroVector()
{
	return FVector3{ 0.f, 0.f, 0.f };
}

void FVector3::Normalize()
{
	X = X * (1.f / sqrt(MATH_DOT(X, X)));
	Y = Y * (1.f / sqrt(MATH_DOT(Y, Y)));
	Z = Z * (1.f / sqrt(MATH_DOT(Z, Z)));
}

bool FVector3::IsZero() const
{
	return X == 0.f && Y == 0.f && Z == 0.f;
}