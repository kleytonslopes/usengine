/*********************************************************************
 *   File: Vector4.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: September 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef KNC_VECTOR_4_HPP
#define	KNC_VECTOR_4_HPP

#include "Core/KyrnnessArch.hpp"
#include "Core/CommonTypes.hpp"
#include <array>
#include <math.h>

class KN_API Vector4
{
	using T = double;
public:
	Vector4() = default;
	Vector4(T x, T y, T z, T w) : m{ x, y, z, w } { }

	~Vector4() = default;

	inline Vector4& operator=(const Vector4& right)
	{
		m[0] = right[0];
		m[1] = right[1];
		m[2] = right[2];
		m[3] = right[3];
		return *this;
	}
	inline Vector4& operator+(const Vector4& right)
	{
		m[0] += right[0];
		m[1] += right[1];
		m[2] += right[2];
		m[3] += right[3];
		return *this;
	}
	inline Vector4& operator-(const Vector4& right)
	{
		m[0] -= right[0];
		m[1] -= right[1];
		m[2] -= right[2];
		m[3] -= right[3];
		return *this;
	}
	inline Vector4& operator*(const Vector4& right)
	{
		m[0] *= right[0];
		m[1] *= right[1];
		m[2] *= right[2];
		m[3] *= right[3];
		return *this;
	}
	inline Vector4& operator/(const Vector4& right)
	{
		m[0] /= right[0];
		m[1] /= right[1];
		m[2] /= right[2];
		m[3] /= right[3];
		if (isnan(m[0])) m[0] = 0.0f;
		if (isnan(m[1])) m[1] = 0.0f;
		if (isnan(m[2])) m[2] = 0.0f;
		if (isnan(m[3])) m[3] = 0.0f;
		return *this;
	}

	inline Vector4& operator+=(const Vector4& right)
	{
		m[0] += right[0];
		m[1] += right[1];
		m[2] += right[2];
		m[3] += right[3];
		return *this;
	}
	inline Vector4& operator-=(const Vector4& right)
	{
		m[0] -= right[0];
		m[1] -= right[1];
		m[2] -= right[2];
		m[3] -= right[3];
		return *this;
	}
	inline Vector4& operator*=(const Vector4& right)
	{
		m[0] *= right[0];
		m[1] *= right[1];
		m[2] *= right[2];
		m[3] *= right[3];
		return *this;
	}
	inline Vector4& operator/=(const Vector4& right)
	{
		m[0] /= right[0];
		m[1] /= right[1];
		m[2] /= right[2];
		m[3] /= right[3];
		if (isnan(m[0])) m[0] = 0.0f;
		if (isnan(m[1])) m[1] = 0.0f;
		if (isnan(m[2])) m[2] = 0.0f;
		if (isnan(m[3])) m[3] = 0.0f;
		return *this;
	}

	inline bool operator==(const Vector4& right) const
	{
		return (m[0] == right[0] && m[1] == right[1] && m[2] == right[2] && m[3] == right[3]);
	}
	inline bool operator!=(const Vector4& right) const
	{
		return (m[0] != right[0] || m[1] != right[1] || m[2] != right[2] || m[3] != right[3]);
	}

	inline const T& operator[](int index) const { return m[index]; }

	T GetX() const { return m[0]; }
	T GetY() const { return m[1]; }
	T GetZ() const { return m[2]; }
	T GetW() const { return m[3]; }

	void SetX(const T& value) { m[0] = value; };
	void SetY(const T& value) { m[1] = value; };
	void SetZ(const T& value) { m[2] = value; };
	void SetW(const T& value) { m[3] = value; };

	inline bool IsZero() const
	{
		return m[0] == 0.0 && m[1] == 0.0 && m[2] == 0.0 && m[3] == 1.0;
	}

	inline void Normalize()
	{
		m[0] = m[0] * (1.f / sqrt(m[0] * m[0]));
		m[1] = m[1] * (1.f / sqrt(m[1] * m[1]));
		m[2] = m[2] * (1.f / sqrt(m[2] * m[2]));
		m[3] = m[3] * (1.f / sqrt(m[3] * m[3]));
	}

	static Vector4 ZeroVector() { return Vector4{ 0.0, 0.0, 0.0, 1.0 }; }

private:
	TArray<T, 4> m{ 0.0, 0.0, 0.0, 1.0 };
};

#endif // !KNC_VECTOR_4_HPP