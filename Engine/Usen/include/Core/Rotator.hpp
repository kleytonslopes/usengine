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

#ifndef US_ROTATOR_HPP
#define	US_ROTATOR_HPP

#include "Core/MinimalCore.hpp"

class AFRotator
{
public:
	float X {0.f};
	float Y {0.f};
	float Z {0.f};
	float W {1.f};

	AFRotator();

	FVector Rotate();

};

#endif // !US_ROTATOR_HPP