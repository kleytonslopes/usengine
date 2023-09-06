/*********************************************************************
 *   File: Rotator.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef KNM_ROTATOR_HPP
#define	KNM_ROTATOR_HPP

#include "Vector3.hpp"
#include "Axis.hpp"

class FRotator
{
public:
	FRotator() = default;
	FRotator(float x, float y, float z);
	FRotator(double x, double y, double z, double w);

	~FRotator() = default;

	FRotator& operator=(const FRotator& right) = default;

	FRotator& operator+(const FRotator& right);
	FRotator& operator-(const FRotator& right);
	FRotator& operator*(const FRotator& right);
	FRotator& operator/(const FRotator& right);

	FRotator& operator+=(const FRotator& right);
	FRotator& operator-=(const FRotator& right);
	FRotator& operator*=(const FRotator& right);
	FRotator& operator/=(const FRotator& right);

	bool operator==(const FRotator& right) const;
	bool operator!=(const FRotator& right) const;

	float& GetX() { return X; }
	float& GetY() { return Y; }
	float& GetZ() { return Z; }
	float& GetW() { return W; }

	void SetX(const float& x);
	void SetY(const float& y);
	void SetZ(const float& z);
	void SetW(const float& w);

	bool IsZero() const;

	static FRotator ZeroRotator();
	static void Rotate(FRotator& rotator, const FVector3& vector);
	static void RatateWithQuartenions(FRotator& rotator, const FVector3& vector);
	static void Rotate(double& x, double& y, double& z, const FRotator& rotator);

	static FRotator Normalize(const FRotator& rotator);
	static FRotator Multiply(const FRotator& rotor1, const FRotator& rotor2);

private:
	float X{ 0.f };
	float Y{ 0.f };
	float Z{ 0.f };
	float W{ 1.f };

	static FRotator AxisRotate(const FRotator& rotator, const float angle, EAxis axis);

	static void RotateInAxisX(FRotator& rotator, const float angle);
	static void RotateInAxisY(FRotator& rotator, const float angle);
	static void RotateInAxisZ(FRotator& rotator, const float angle);


};

#endif // !KNM_ROTATOR_HPP



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
