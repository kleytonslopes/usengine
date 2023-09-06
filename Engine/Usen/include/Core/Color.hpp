/*********************************************************************
 *   File: Color.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_COLOR_HPP
#define	US_COLOR_HPP

class FColor
{
public:
	float R { 0.f };
	float G { 0.f };
	float B { 0.f };
	float A { 1.f };

	FColor() = default;
	FColor(float r, float g, float b, float a);

	static FColor White;
	static FColor Black;
	static FColor Red;
	static FColor Green;
	static FColor Blue;
	static FColor Cyan;
	static FColor Pink;
	static FColor Yellow;
	static FColor Orange;
	static FColor Purple;
};

#endif // !US_COLOR_HPP