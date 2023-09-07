/*********************************************************************
 *   File: Rotator.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "Rotator.hpp"
#include "Math.hpp"
#include <cmath>
#include <array>

FRotator::FRotator(float x, float y, float z)
	: X{ x }
	, Y{ y }
	, Z{ z }
{ }

FRotator::FRotator(double x, double y, double z, double w)
	: X{ (float)x }
	, Y{ (float)y }
	, Z{ (float)x }
	, W{ (float)w }
{ }

FRotator& FRotator::operator+(const FRotator& right)
{
	this->X += right.X;
	this->Y += right.Y;
	this->Z += right.Z;
	this->W = right.W;

	return *this;
}
FRotator& FRotator::operator-(const FRotator& right)
{
	this->X -= right.X;
	this->Y -= right.Y;
	this->Z -= right.Z;
	this->W = right.W;

	return *this;
}
FRotator& FRotator::operator*(const FRotator& right)
{
	this->X *= right.X;
	this->Y *= right.Y;
	this->Z *= right.Z;
	this->W = right.W;

	return *this;
}
FRotator& FRotator::operator/(const FRotator& right)
{
	this->X /= right.X;
	this->Y /= right.Y;
	this->Z /= right.Z;
	this->W = right.W;

	FMath::ResolveNaN(X);
	FMath::ResolveNaN(Y);
	FMath::ResolveNaN(Z);

	return *this;
}

FRotator& FRotator::operator+=(const FRotator& right)
{
	this->X += right.X;
	this->Y += right.Y;
	this->Z += right.Z;
	this->W = right.W;

	return *this;
}
FRotator& FRotator::operator-=(const FRotator& right)
{
	this->X -= right.X;
	this->Y -= right.Y;
	this->Z -= right.Z;
	this->W = right.W;

	return *this;
}
FRotator& FRotator::operator*=(const FRotator& right)
{
	this->X *= right.X;
	this->Y *= right.Y;
	this->Z *= right.Z;
	this->W = right.W;

	return *this;
}
FRotator& FRotator::operator/=(const FRotator& right)
{
	this->X /= right.X;
	this->Y /= right.Y;
	this->Z /= right.Z;
	this->W = right.W;

	FMath::ResolveNaN(X);
	FMath::ResolveNaN(Y);
	FMath::ResolveNaN(Z);

	return *this;
}

bool FRotator::operator==(const FRotator& right) const
{
	return X == right.X && Y == right.Y && Z == right.Z && W == right.W;
}
bool FRotator::operator!=(const FRotator& right) const
{
	return X != right.X || Y != right.Y || Z != right.Z || W != right.W;
}

void FRotator::SetX(const float& x)
{
	X = x;
}
void FRotator::SetY(const float& y)
{
	Y = y;
}
void FRotator::SetZ(const float& z)
{
	Z = z;
}
void FRotator::SetW(const float& w)
{
	W = w;
}

bool FRotator::IsZero() const
{
	return X == 0.f && Y == 0.f && Z == 0.f && Z == 1.f;
}

FRotator FRotator::ZeroRotator()
{
	return FRotator();
}

void FRotator::Rotate(FRotator& rotator, const FVector3& vector)
{
	RotateInAxisX(rotator, FMath::Radians(vector.GetX()));
	RotateInAxisY(rotator, FMath::Radians(vector.GetY()));
	RotateInAxisZ(rotator, FMath::Radians(vector.GetZ()));
	
}

void FRotator::Rotate(double& x, double& y, double& z, const FRotator& rotator)
{
	FRotator vectorQuaternion(0.0, x, y, z);
	FRotator conjugate = FRotator(-rotator.X, -rotator.Y, -rotator.Z, rotator.W);

	FRotator rotatedVectorQuaternion = FRotator::Multiply(FRotator::Multiply(rotator, vectorQuaternion), conjugate);

	x = rotatedVectorQuaternion.X;
	y = rotatedVectorQuaternion.Y;
	z = rotatedVectorQuaternion.Z;
}

FRotator FRotator::Normalize(const FRotator& rotator)
{
	double magnitude = std::sqrt(rotator.W * rotator.W + rotator.X * rotator.X + rotator.Y * rotator.Y + rotator.Z * rotator.Z);
	return FRotator(rotator.X / magnitude, rotator.Y / magnitude, rotator.Z / magnitude, rotator.W / magnitude);
}

FRotator FRotator::Multiply(const FRotator& rotor1, const FRotator& rotor2)
{
	return FRotator(
		rotor1.W * rotor2.X + rotor1.X * rotor2.W + rotor1.Y * rotor2.Z - rotor1.Z * rotor2.Y,
		rotor1.W * rotor2.Y - rotor1.X * rotor2.Z + rotor1.Y * rotor2.W + rotor1.Z * rotor2.X,
		rotor1.W * rotor2.Z + rotor1.X * rotor2.Y - rotor1.Y * rotor2.X + rotor1.Z * rotor2.W,
		rotor1.W * rotor2.W - rotor1.X * rotor2.X - rotor1.Y * rotor2.Y - rotor1.Z * rotor2.Z
	);
}

FRotator FRotator::AxisRotate(const FRotator& rotator, const float angle, EAxis axis)
{
	float aCos = cos(angle);
	float aSin = sin(angle);

	float axisX;
	float axisY;
	float axisZ;

	switch (axis)
	{
	case EAxis::X:
		axisX = 1.f;
		axisY = 0.f;
		axisZ = 0.f;
		break;
	case EAxis::Y:
		axisX = 0.f;
		axisY = 1.f;
		axisZ = 0.f;
		break;
	case EAxis::Z:
		axisX = 0.f;
		axisY = 0.f;
		axisZ = 1.f;
		break;
	}



	float a = (1.f - aCos) * axisX; //temp[0]
	float b = (1.f - aCos) * axisY; //temp[1]
	float c = (1.f - aCos) * axisZ; //temp[2]

	std::array<std::array<float, 4>, 4> rotor;
	rotor[0][0] = aCos + a * axisX;
	rotor[0][1] = a * axisY + aSin * axisZ;
	rotor[0][2] = a * axisZ - aSin * axisY;

	rotor[1][0] = b * axisX - aSin * axisZ;
	rotor[1][1] = aCos + b * axisY;
	rotor[1][2] = b * axisZ + aSin * axisX;

	rotor[2][0] = c * axisX + aSin * axisY;
	rotor[2][1] = c * axisY - aSin * axisX;
	rotor[2][2] = aCos + c * axisZ;

	FRotator result{};
	result.X = rotator.X * rotor[0][0] + rotator.Y * rotor[0][1] + rotator.Z * rotor[0][2];
	result.Y = rotator.X * rotor[1][0] + rotator.Y * rotor[1][1] + rotator.Z * rotor[1][2];
	result.Z = rotator.X * rotor[2][0] + rotator.Y * rotor[2][1] + rotator.Z * rotor[2][2];
	result.W = rotator.W;

	return result;
}

void FRotator::RotateInAxisX(FRotator& rotator, const float angle)
{
	double cosA = cos(angle);
	double sinA = sin(angle);

	///double tempX = rotator.X;
	double tempY = rotator.Y;
	double tempZ = rotator.Z;

	rotator.Y = cosA * tempY - sinA * tempZ;
	rotator.Z = sinA * tempY + cosA * tempZ;
}

void FRotator::RotateInAxisY(FRotator& rotator, const float angle)
{
	double cosA = cos(angle);
	double sinA = sin(angle);

	double tempX = rotator.X;
	///double tempY = rotator.Y;
	double tempZ = rotator.Z;

	rotator.X = cosA * tempX + sinA * tempZ;
	rotator.Z = -sinA * tempX + cosA * tempZ;
}

void FRotator::RotateInAxisZ(FRotator& rotator, const float angle)
{
	double cosA = cos(angle);
	double sinA = sin(angle);

	double tempX = rotator.X;
	double tempY = rotator.Y;
	//double tempZ = rotator.Z;

	rotator.X = cosA * tempX - sinA * tempY;
	rotator.Y = sinA * tempX + cosA * tempY;
}



/*

	--     --
 x | 1  0  0 |
 y | 0  1  0 |
 z | 0  0  1 |
	--     --
	e1 e2 e3
*/


/*
#include <iostream>
#include <cmath>

// Function to rotate a 3D vector (x, y, z) around a specific axis by an angle (in radians)
void rotateVector(double& x, double& y, double& z, char axis, double angle) {
	double cosA = cos(angle);
	double sinA = sin(angle);

	double tempX = x;
	double tempY = y;
	double tempZ = z;

	if (axis == 'X' || axis == 'x') {
		y = cosA * tempY - sinA * tempZ;
		z = sinA * tempY + cosA * tempZ;
	} else if (axis == 'Y' || axis == 'y') {
		x = cosA * tempX + sinA * tempZ;
		z = -sinA * tempX + cosA * tempZ;
	} else if (axis == 'Z' || axis == 'z') {
		x = cosA * tempX - sinA * tempY;
		y = sinA * tempX + cosA * tempY;
	} else {
		std::cerr << "Invalid axis specified." << std::endl;
	}
}

int main() {
	double x = 1.0; // Initial X component
	double y = 0.0; // Initial Y component
	double z = 0.0; // Initial Z component

	char axis = 'Y'; // Axis of rotation ('X', 'Y', or 'Z')
	double angle = 45.0 * M_PI / 180.0; // Angle in radians

	std::cout << "Original Vector: (" << x << ", " << y << ", " << z << ")" << std::endl;

	rotateVector(x, y, z, axis, angle);

	std::cout << "Rotated Vector: (" << x << ", " << y << ", " << z << ")" << std::endl;

	return 0;
}
*/



/*
#include <iostream>
#include <cmath>

// Quaternion structure
struct Quaternion {
	double w, x, y, z;

	Quaternion(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {}
};

// Function to normalize a quaternion
Quaternion normalize(const Quaternion& q) {
	double magnitude = std::sqrt(q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z);
	return Quaternion(q.w/magnitude, q.x/magnitude, q.y/magnitude, q.z/magnitude);
}

// Function to multiply two quaternions
Quaternion multiply(const Quaternion& q1, const Quaternion& q2) {
	return Quaternion(
		q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z,
		q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y,
		q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x,
		q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w
	);
}

// Function to rotate a vector using a quaternion
void rotateVectorWithQuaternion(double& x, double& y, double& z, const Quaternion& rotationQuaternion) {
	Quaternion vectorQuaternion(0.0, x, y, z);
	Quaternion conjugate = Quaternion(rotationQuaternion.w, -rotationQuaternion.x, -rotationQuaternion.y, -rotationQuaternion.z);

	Quaternion rotatedVectorQuaternion = multiply(multiply(rotationQuaternion, vectorQuaternion), conjugate);

	x = rotatedVectorQuaternion.x;
	y = rotatedVectorQuaternion.y;
	z = rotatedVectorQuaternion.z;
}

int main() {
	double x = 1.0; // Initial X component
	double y = 0.0; // Initial Y component
	double z = 0.0; // Initial Z component

	double angle = 45.0 * M_PI / 180.0; // Angle in radians

	double axisX = 0.0;
	double axisY = 1.0;
	double axisZ = 0.0;

	// Create the rotation quaternion
	Quaternion rotationQuaternion(std::cos(angle / 2.0), axisX * std::sin(angle / 2.0), axisY * std::sin(angle / 2.0), axisZ * std::sin(angle / 2.0));
	rotationQuaternion = normalize(rotationQuaternion);

	std::cout << "Original Vector: (" << x << ", " << y << ", " << z << ")" << std::endl;

	rotateVectorWithQuaternion(x, y, z, rotationQuaternion);

	std::cout << "Rotated Vector: (" << x << ", " << y << ", " << z << ")" << std::endl;

	return 0;
}

*/





/**
#include <iostream>
#include <cmath>

// Quaternion structure
struct Quaternion {
	double w, x, y, z;

	Quaternion(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {}
};

// Function to normalize a quaternion
Quaternion normalize(const Quaternion& q) {
	double magnitude = std::sqrt(q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z);
	return Quaternion(q.w/magnitude, q.x/magnitude, q.y/magnitude, q.z/magnitude);
}

// Function to multiply two quaternions
Quaternion multiply(const Quaternion& q1, const Quaternion& q2) {
	return Quaternion(
		q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z,
		q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y,
		q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x,
		q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w
	);
}

// Function to rotate a vector using a quaternion
void rotateVectorWithQuaternion(double& x, double& y, double& z, const Quaternion& rotationQuaternion) {
	Quaternion vectorQuaternion(0.0, x, y, z);
	Quaternion conjugate = Quaternion(rotationQuaternion.w, -rotationQuaternion.x, -rotationQuaternion.y, -rotationQuaternion.z);

	Quaternion rotatedVectorQuaternion = multiply(multiply(rotationQuaternion, vectorQuaternion), conjugate);

	x = rotatedVectorQuaternion.x;
	y = rotatedVectorQuaternion.y;
	z = rotatedVectorQuaternion.z;
}

int main() {
	double x = 1.0; // Initial X component
	double y = 0.0; // Initial Y component
	double z = 0.0; // Initial Z component

	double angleX = 45.0 * M_PI / 180.0; // Angle in radians for rotation around X-axis
	double angleY = 30.0 * M_PI / 180.0; // Angle in radians for rotation around Y-axis
	double angleZ = 60.0 * M_PI / 180.0; // Angle in radians for rotation around Z-axis

	// Create the rotation quaternions for each axis
	Quaternion rotationQuaternionX(std::cos(angleX / 2.0), std::sin(angleX / 2.0), 0.0, 0.0);
	Quaternion rotationQuaternionY(std::cos(angleY / 2.0), 0.0, std::sin(angleY / 2.0), 0.0);
	Quaternion rotationQuaternionZ(std::cos(angleZ / 2.0), 0.0, 0.0, std::sin(angleZ / 2.0));

	rotationQuaternionX = normalize(rotationQuaternionX);
	rotationQuaternionY = normalize(rotationQuaternionY);
	rotationQuaternionZ = normalize(rotationQuaternionZ);

	std::cout << "Original Vector: (" << x << ", " << y << ", " << z << ")" << std::endl;

	// Rotate around X-axis
	rotateVectorWithQuaternion(x, y, z, rotationQuaternionX);

	std::cout << "Rotated Vector X: (" << x << ", " << y << ", " << z << ")" << std::endl;

	// Reset vector
	x = 1.0;
	y = 0.0;
	z = 0.0;

	// Rotate around Y-axis
	rotateVectorWithQuaternion(x, y, z, rotationQuaternionY);

	std::cout << "Rotated Vector Y: (" << x << ", " << y << ", " << z << ")" << std::endl;

	// Reset vector
	x = 1.0;
	y = 0.0;
	z = 0.0;

	// Rotate around Z-axis
	rotateVectorWithQuaternion(x, y, z, rotationQuaternionZ);

	std::cout << "Rotated Vector Z: (" << x << ", " << y << ", " << z << ")" << std::endl;

	return 0;
}
*/





