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
#include "Vector3.hpp"

#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif

#ifndef M_PIR
#define M_PIR    180.000
#endif

#define MATH_CLAMP(V, MN, MX) V > MX ? MX : (V < MN ? MN : V)
#define MATH_DOT(A, B) A * B

class FMath
{
public:
	inline static void ResolveNaN(float& value)
	{
		if (isnan(value)) value = 0.0f;
	}
	inline static void ResolveNaN(double& value)
	{
		if (isnan(value)) value = 0.0f;
	}

	inline static double Radians(const double& degrees)
	{
		return (degrees * M_PI) / M_PIR;
	}

	inline static double Degrees(const double& radian)
	{
		return (radian * M_PIR) / M_PI;
	}

	inline static float Clamp(const float& value, float min, float max) { return MATH_CLAMP(value, min, max); }
	inline static double Clamp(const double& value, double min, double max) { return MATH_CLAMP(value, min, max); }
	inline static unsigned char Clamp(const unsigned char& value, unsigned char min, unsigned char max) { return MATH_CLAMP(value, min, max); }
	inline static unsigned short int Clamp(const unsigned short int& value, unsigned short int min, unsigned short int max) { return MATH_CLAMP(value, min, max); }
	inline static unsigned int Clamp(const unsigned int& value, unsigned int min, unsigned int max) { return MATH_CLAMP(value, min, max); }
	inline static unsigned long long Clamp(const unsigned long long& value, unsigned long long min, unsigned long long max) { return MATH_CLAMP(value, min, max); }
	inline static signed char Clamp(const signed char& value, signed char min, signed char max) { return MATH_CLAMP(value, min, max); }
	inline static signed short int Clamp(const signed short int& value, signed short int min, signed short int max) { return MATH_CLAMP(value, min, max); }
	inline static signed int Clamp(const signed int& value, signed int min, signed int max) { return MATH_CLAMP(value, min, max); }
	inline static signed long long Clamp(const signed long long& value, signed long long min, signed long long max) { return MATH_CLAMP(value, min, max); }

	inline static float Dot(const FVector3& a, const FVector3& b) 
	{ 
		return 0.f;/*  MATH_DOT(a.X, b.X) + MATH_DOT(a.Y, b.Y) + MATH_DOT(a.Z, b.Z);*/
	}
};

