/*********************************************************************
 *   File: Vector3.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: September 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef KNC_VECTOR_3_HPP
#define	KNC_VECTOR_3_HPP

#include "Core/KyrnnessArch.hpp"
#include "Core/CommonTypes.hpp"
#include <array>
#include <math.h>

class KN_API Vector3
{
public:
	using T = double;

	Vector3() = default;
	Vector3(const Vector3& vector) = default;
	Vector3(T x, T y, T z) : m{ x, y, z } { }

	~Vector3() = default;

	Vector3& operator=(const Vector3& right);

	Vector3& operator+=(const Vector3& right);
	Vector3& operator+=(const T& scale);

	Vector3& operator-=(const Vector3& right);
	Vector3& operator-=(const T& scale);

	Vector3& operator*=(const Vector3& right);
	Vector3& operator*=(const T& scale);

	Vector3& operator/=(const Vector3& right);
	Vector3& operator/=(const T& scale);

	bool operator==(const Vector3& right) const;
	bool operator!=(const Vector3& right) const;

	const T& operator[](int index) const { return m[index]; }

	T GetX() const { return m[0]; }
	T GetY() const { return m[1]; }
	T GetZ() const { return m[2]; }

	void SetX(const T& value) { m[0] = value; };
	void SetY(const T& value) { m[1] = value; };
	void SetZ(const T& value) { m[2] = value; };

	inline bool IsZero() const
	{
		return m[0] == 0.0 && m[1] == 0.0 && m[2] == 0.0;
	}

	static Vector3 Normalize(const Vector3& vector);

	static T Dot(const Vector3& a, const Vector3& b);

	static Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		return Vector3
		{
			a[1] * b[2] - b[1] * a[2],
			a[2] * b[0] - b[2] * a[0],
			a[0] * b[1] - b[0] * a[1]
		};
	}

	static Vector3 ZeroVector() { return Vector3{ 0.0, 0.0, 0.0 }; }

private:
	TArray<T, 3> m{ 0.0, 0.0, 0.0 };

	friend class Location;
};

Vector3 operator+(const Vector3& left, const Vector3& right);
Vector3 operator+(const Vector3::T& scalar, const Vector3& right);
Vector3 operator+(const Vector3& right, const Vector3::T& scalar);

Vector3 operator-(const Vector3& left, const Vector3& right);
Vector3 operator-(const Vector3::T& scalar, const Vector3& right);
Vector3 operator-(const Vector3& right, const Vector3::T& scalar);

Vector3 operator*(const Vector3& left, const Vector3& right);
Vector3 operator*(const Vector3::T& scalar, const Vector3& right);
Vector3 operator*(const Vector3& right, const Vector3::T& scalar);

#endif // !KNC_VECTOR_3_HPP
