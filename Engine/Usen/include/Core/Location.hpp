/*********************************************************************
 *   File: Location.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: September 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once


#ifndef KNC_LOCATION_HPP
#define	KNC_LOCATION_HPP

#include "Core/Vectors/Vector3.hpp"

class KN_API Location
{
	using T = double;
public:
	Location() = default;
	Location(T x, T y, T z) : m{ x, y, z } { }

	~Location() = default;

	operator Vector3& () { return Vector3{m[0], m[1], m[2] }; }

	Location& operator=(const Location& right) = default;
	inline Location& operator+(const Location& right)
	{
		m += right.m;
		return *this;
	}
	inline Location& operator-(const Location& right)
	{
		m -= right.m;
		return *this;
	}

	inline Location& operator*(const Location& right)
	{
		m *= right.m;
		return *this;
	}
	inline Location& operator/(const Location& right)
	{
		m /= right.m;
		return *this;
	}

	inline Location& operator+=(const Location& right)
	{
		m += right.m;
		return *this;
	}
	inline Location& operator-=(const Location& right)
	{
		m -= right.m;
		return *this;
	}
	inline Location& operator*=(const Location& right)
	{
		m *= right.m;
		return *this;
	}
	inline Location& operator/=(const Location& right)
	{
		m /= right.m;
		return *this;
	}

	inline bool operator==(const Location& right) const
	{
		return (m == right.m);
	}
	inline bool operator!=(const Location& right) const
	{
		return (m != right.m);
	}

	inline const T& operator[](int index) const { return m[index]; }

	T GetX() const { return m.GetX(); }
	T GetY() const { return m.GetY(); }
	T GetZ() const { return m.GetZ(); }

	void SetX(const T& value) { m.SetX(value); };
	void SetY(const T& value) { m.SetY(value); };
	void SetZ(const T& value) { m.SetZ(value); };

private:
	Vector3 m;
};

#endif // !KNC_LOCATION_HPP