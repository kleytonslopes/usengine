/*********************************************************************
 *   File: Vector2.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: September 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef KNC_VECTOR_2_HPP
#define	KNC_VECTOR_2_HPP

#include "Core/KyrnnessArch.hpp"
#include "Core/CommonTypes.hpp"
#include <array>
#include <math.h>

class KN_API Vector2
{
	using T = double;
public:
	Vector2() = default;
	Vector2(T x, T y) : m{ x, y } { }

	~Vector2() = default;

	inline Vector2& operator=(const Vector2& right) 
	{
		m[0] = right[0];
		m[1] = right[1];
		return *this;
	}
	inline Vector2& operator+(const Vector2& right)
	{
		m[0] += right[0];
		m[1] += right[1];
		return *this;
	}
	inline Vector2& operator-(const Vector2& right)
	{
		m[0] -= right[0];
		m[1] -= right[1];
		return *this;
	}
	inline Vector2& operator*(const Vector2& right)
	{
		m[0] *= right[0];
		m[1] *= right[1];
		return *this;
	}
	inline Vector2& operator/(const Vector2& right)
	{
		m[0] /= right[0];
		m[1] /= right[1];
		if (isnan(m[0])) m[0] = 0.0f;
		if (isnan(m[1])) m[1] = 0.0f;
		return *this;
	}

	inline Vector2& operator+=(const Vector2& right)
	{
		m[0] += right[0];
		m[1] += right[1];
		return *this;
	}
	inline Vector2& operator-=(const Vector2& right)
	{
		m[0] -= right[0];
		m[1] -= right[1];
		return *this;
	}
	inline Vector2& operator*=(const Vector2& right)
	{
		m[0] *= right[0];
		m[1] *= right[1];
		return *this;
	}
	inline Vector2& operator/=(const Vector2& right)
	{
		m[0] /= right[0];
		m[1] /= right[1];
		if (isnan(m[0])) m[0] = 0.0f;
		if (isnan(m[1])) m[1] = 0.0f;
		return *this;
	}

	inline bool operator==(const Vector2& right) const
	{
		return (m[0] == right[0] && m[1] == right[1]);
	}
	inline bool operator!=(const Vector2& right) const
	{
		return (m[0] != right[0] || m[1] != right[1]);
	}

	inline const T& operator[](int index) const { return m[index]; }

	T GetX() const { return m[0]; }
	T GetY() const { return m[1]; }

	void SetX(const T& value) { m[0] = value; };
	void SetY(const T& value) { m[1] = value; };

	inline bool IsZero() const
	{
		return m[0] == 0.0 && m[1] == 0.0;
	}

	inline void Normalize()
	{
		m[0] = m[0] * (1.f / sqrt(m[0] * m[0]));
		m[1] = m[1] * (1.f / sqrt(m[1] * m[1]));
	}

	static Vector2 ZeroVector() { return Vector2{ 0.0, 0.0 }; }

private:
	TArray<T, 2> m{ 0.0, 0.0 };
};

#endif // !KNC_VECTOR_2_HPP