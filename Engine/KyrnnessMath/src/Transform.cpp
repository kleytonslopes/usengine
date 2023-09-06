/*********************************************************************
 *   File: Transform.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "Transform.hpp"

FVector3 FTransform::AxisX{ 1.f, 0.f, 0.f };
FVector3 FTransform::AxisY{ 0.f, 1.f, 0.f };
FVector3 FTransform::AxisZ{ 0.f, 0.f, 1.f };
FVector3 FTransform::WorldUpVector{0.f, 1.f, 0.f };
FVector3 FTransform::WorldForwardVector{0.f, 0.f, -1.f };
FVector3 FTransform::WorldRightVector{-1.f, 0.f, 0.f };

FTransform::FTransform(FVector3 location)
	: Location{ location }
{

}

FTransform& FTransform::operator+(const FTransform& right)
{
	this->Location      += right.Location;
	this->Origin        += right.Origin;
	this->Scale         += right.Scale;
	this->Rotation      += right.Rotation;

	return *this;
}

FTransform& FTransform::operator-(const FTransform& right)
{
	this->Location      -= right.Location;
	this->Origin        -= right.Origin;
	this->Scale         -= right.Scale;
	this->Rotation      -= right.Rotation;

	return *this;
}
FTransform& FTransform::operator*(const FTransform& right)
{
	this->Location      *= right.Location;
	this->Origin        *= right.Origin;
	this->Scale         *= right.Scale;
	this->Rotation      *= right.Rotation;

	return *this;
}
FTransform& FTransform::operator/(const FTransform& right)
{
	this->Location      /= right.Location;
	this->Origin        /= right.Origin;
	this->Scale         /= right.Scale;
	this->Rotation      /= right.Rotation;

	return *this;
}

FTransform& FTransform::operator+=(const FTransform& right)
{
	this->Location      += right.Location;
	this->Origin        += right.Origin;
	this->Scale         += right.Scale;
	this->Rotation      += right.Rotation;

	return *this;
}
FTransform& FTransform::operator-=(const FTransform& right)
{
    this->Location      -= right.Location;
	this->Origin        -= right.Origin;
	this->Scale         -= right.Scale;
	this->Rotation      -= right.Rotation;

	return *this;
}
FTransform& FTransform::operator*=(const FTransform& right)
{
	this->Location      *= right.Location;
	this->Origin        *= right.Origin;
	this->Scale         *= right.Scale;
	this->Rotation      *= right.Rotation;

	return *this;
}
FTransform& FTransform::operator/=(const FTransform& right)
{
	this->Location      /= right.Location;
	this->Origin        /= right.Origin;
	this->Scale         /= right.Scale;
	this->Rotation      /= right.Rotation;

	return *this;
}

bool FTransform::operator==(const FTransform& right) const
{
	return this->Location == right.Location
		&& this->Origin   == right.Origin
		&& this->Scale    == right.Scale
		&& this->Rotation == right.Rotation;
}
bool FTransform::operator!=(const FTransform& right) const
{
	return this->Location != right.Location
		|| this->Origin   != right.Origin
		|| this->Scale    != right.Scale
		|| this->Rotation != right.Rotation;
}

void FTransform::SetLocation(const FVector3& vector)
{
	Location = vector;
}
void FTransform::SetOrigin(const FVector3& vector)
{
	Origin = vector;
}
void FTransform::SetRotation(const FRotator& rotator)
{
	Rotation = rotator;
}
void FTransform::SetScale(const FVector3& vector)
{
	Scale = vector;
}
void FTransform::SetUpVector(const FVector3& vector)
{
	UpVector = vector;
}
void FTransform::SetForwardVector(const FVector3& vector)
{
	ForwardVector = vector;
}
