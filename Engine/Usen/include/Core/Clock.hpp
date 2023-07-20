/*********************************************************************
 *   File: Clock.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#include "Core/CommonTypes.hpp"

struct FTime
{
	us::types::FCommonTypes::Time Time;

	FTime() = default;
	static FTime Now();

private:
	FTime(us::types::FCommonTypes::Time newTime);
};

struct FClock
{
	static FTime Now();
	static float Duration(const FTime& newTime, const FTime& currentTime);
};