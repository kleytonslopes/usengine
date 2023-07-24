/*********************************************************************
 *   File: Clock.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CLOCK_HPP
#define	US_CLOCK_HPP

#include "Core/CommonTypes.hpp"

class FTime
{
public:
	us::types::FCommonTypes::Time Time;

	FTime() = default;
	static FTime Now();

private:
	FTime(us::types::FCommonTypes::Time newTime);

};

class FClock
{
public:
	static FTime Now();
	static float Duration(const FTime& newTime, const FTime& currentTime);
};

#endif // !US_CLOCK_HPP