/*********************************************************************
 *   File: Clock.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Core/Clock.hpp"


FTime::FTime(us::types::FCommonTypes::Time newTime)
{
	Time = newTime;
}

FTime FTime::Now()
{
	return FTime::FTime(us::types::FCommonTypes::Clock::now());
}

FTime FClock::Now()
{
	return FTime::Now();
}

float FClock::Duration(const FTime& newTime, const FTime& currentTime)
{
	return std::chrono::duration<float, us::types::FCommonTypes::Seconds::period>(newTime.Time - currentTime.Time).count();
}