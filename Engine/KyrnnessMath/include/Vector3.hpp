/*********************************************************************
 *   File: Vector.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef KNM_VECTOR_3_HPP
#define	KNM_VECTOR_3_HPP

class FVector3
{
	using T = double;
public:
	T X { 0.0 };
	T Y { 0.0 };
	T Z { 0.0 };

	FVector3() = default;
	FVector3(T x, T y, T z);

	~FVector3() = default;

	FVector3& operator=(const FVector3& right) = default;
	FVector3& operator+(const FVector3& right);
	FVector3& operator-(const FVector3& right);
	FVector3& operator*(const FVector3& right);
	FVector3& operator/(const FVector3& right);

	FVector3& operator+=(const FVector3& right);
	FVector3& operator-=(const FVector3& right);
	FVector3& operator*=(const FVector3& right);
	FVector3& operator/=(const FVector3& right);

	bool operator==(const FVector3& right) const;
	bool operator!=(const FVector3& right) const;


	T GetX() const { return X; }
	T GetY() const { return Y; }
	T GetZ() const { return Z; }

	void SetX(const T& x);
	void SetY(const T& y);
	void SetZ(const T& z);

	bool IsZero() const;

	static FVector3 ZeroVector();
	void Normalize();

};

#endif // !KNM_VECTOR_3_HPP
