/*********************************************************************
 *   File: Math.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#pragma once

#include <math.h>
#include "Core/Vectors/Vector3.hpp"
#include "Core/CommonTypes.hpp"

#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif

#ifndef M_PIR
#define M_PIR    180.000
#endif

#define MATH_CLAMP(V, MN, MX) V > MX ? MX : (V < MN ? MN : V)

class FMath
{
public:
	INLINE_STATIC void ResolveNaN(float& value)
	{
		if (isnan(value)) value = 0.0f;
	}
	INLINE_STATIC void ResolveNaN(double& value)
	{
		if (isnan(value)) value = 0.0f;
	}

	INLINE_STATIC double Radians(const double& degrees)
	{
		return (degrees * M_PI) / M_PIR;
	}

	INLINE_STATIC double Degrees(const double& radian)
	{
		return (radian * M_PIR) / M_PI;
	}

	INLINE_STATIC float Clamp(const float& value, float min, float max) { return MATH_CLAMP(value, min, max); }
	INLINE_STATIC double Clamp(const double& value, double min, double max) { return MATH_CLAMP(value, min, max); }
	INLINE_STATIC uint8 Clamp(const uint8& value, uint8 min, uint8 max) { return MATH_CLAMP(value, min, max); }
	INLINE_STATIC uint16 Clamp(const uint16& value, uint16 min, uint16 max) { return MATH_CLAMP(value, min, max); }
	INLINE_STATIC uint32 Clamp(const uint32& value, uint32 min, uint32 max) { return MATH_CLAMP(value, min, max); }
	INLINE_STATIC uint64 Clamp(const uint64& value, uint64 min, uint64 max) { return MATH_CLAMP(value, min, max); }
	INLINE_STATIC int8 Clamp(const int8& value, int8 min, int8 max) { return MATH_CLAMP(value, min, max); }
	INLINE_STATIC int16 Clamp(const int16& value, int16 min, int16 max) { return MATH_CLAMP(value, min, max); }
	INLINE_STATIC int32 Clamp(const int32& value, int32 min, int32 max) { return MATH_CLAMP(value, min, max); }
	INLINE_STATIC int64 Clamp(const int64& value, int64 min, int64 max) { return MATH_CLAMP(value, min, max); }

	INLINE_STATIC double Dot(const Vector3& a, const Vector3& b) { return Vector3::Dot(a, b); }


};

