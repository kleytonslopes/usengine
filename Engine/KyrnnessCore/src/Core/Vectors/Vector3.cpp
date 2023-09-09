/*********************************************************************
 *   File: Vector3.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: September 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "Core/Vectors/Vector3.hpp"

Vector3& Vector3::operator=(const Vector3& right)
{
	m[0] = right[0];
	m[1] = right[1];
	m[2] = right[2];
	return *this;
}

Vector3& Vector3::operator+=(const Vector3& right)
{
	m[0] += right[0];
	m[1] += right[1];
	m[2] += right[2];
	return *this;
}
Vector3& Vector3::operator+=(const T& scale)
{
	m[0] += scale;
	m[1] += scale;
	m[2] += scale;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& right)
{
	m[0] -= right[0];
	m[1] -= right[1];
	m[2] -= right[2];
	return *this;
}
Vector3& Vector3::operator-=(const T& scale)
{
	m[0] -= scale;
	m[1] -= scale;
	m[2] -= scale;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& right)
{
	m[0] *= right[0];
	m[1] *= right[1];
	m[2] *= right[2];
	return *this;
}
Vector3& Vector3::operator*=(const T& scale)
{
	m[0] *= scale;
	m[1] *= scale;
	m[2] *= scale;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& right)
{
	m[0] /= right[0];
	m[1] /= right[1];
	m[2] /= right[2];
	if (isnan(m[0])) m[0] = 0.0f;
	if (isnan(m[1])) m[1] = 0.0f;
	if (isnan(m[2])) m[2] = 0.0f;
	return *this;
}
Vector3& Vector3::operator/=(const T& scale)
{
	m[0] /= scale;
	m[1] /= scale;
	m[2] /= scale;
	if (isnan(m[0])) m[0] = 0.0f;
	if (isnan(m[1])) m[1] = 0.0f;
	if (isnan(m[2])) m[2] = 0.0f;
	return *this;
}

bool Vector3::operator==(const Vector3& right) const
{
	return (m[0] == right[0] && m[1] == right[1] && m[2] == right[2]);
}
bool Vector3::operator!=(const Vector3& right) const
{
	return (m[0] != right[0] || m[1] != right[1] || m[2] != right[2]);
}

Vector3 operator+(const Vector3& left, const Vector3& right)
{
	return Vector3(
		left[0] + right[0],
		left[1] + right[1],
		left[2] + right[2]
	);
}
Vector3 operator+(const Vector3::T& scalar, const Vector3& right)
{
	return Vector3(
		scalar + right[0],
		scalar + right[1],
		scalar + right[2]
	);
}
Vector3 operator+(const Vector3& right, const Vector3::T& scalar)
{
	return Vector3(
		right[0] + scalar,
		right[1] + scalar,
		right[2] + scalar
	);
}

Vector3 operator-(const Vector3& left, const Vector3& right)
{
	return Vector3(
		left[0] - right[0],
		left[1] - right[1],
		left[2] - right[2]
	);
}
Vector3 operator-(const Vector3::T& scalar, const Vector3& right)
{
	return Vector3(
		scalar - right[0],
		scalar - right[1],
		scalar - right[2]
	);
}
Vector3 operator-(const Vector3& right, const Vector3::T& scalar)
{
	return Vector3(
		right[0] - scalar,
		right[1] - scalar,
		right[2] - scalar
	);
}

Vector3 operator*(const Vector3& left, const Vector3& right)
{
	return Vector3(
		left[0] * right[0],
		left[1] * right[1],
		left[2] * right[2]
	);
}
Vector3 operator*(const Vector3::T& scalar, const Vector3& right)
{
	return Vector3(
		scalar * right[0],
		scalar * right[1],
		scalar * right[2]
	);
}
Vector3 operator*(const Vector3& right, const Vector3::T& scalar)
{
	return Vector3(
		right[0] * scalar,
		right[1] * scalar,
		right[2] * scalar
	);
}



Vector3 Vector3::Normalize(const Vector3& vector)
{
	return vector * (static_cast<Vector3::T>(1) / sqrt(Vector3::Dot(vector, vector)));
}

Vector3::T Vector3::Dot(const Vector3& a, const Vector3& b)
{
	Vector3 dotP(a * b);

	return (dotP[0] + dotP[1] + dotP[2]);
}