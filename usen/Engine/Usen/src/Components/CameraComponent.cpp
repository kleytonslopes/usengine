/*********************************************************************
 *   File: CameraComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Components/CameraComponent.hpp"

UCameraComponent::UCameraComponent()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UCameraComponent::~UCameraComponent()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UCameraComponent::Serialize(SeriFile& otherOut)
{
	BeginComponentSection(otherOut, Identity);

	Key(otherOut, "near", Near);
	Key(otherOut, "far", Far);
	Key(otherOut, "fov", Fov);
	Key(otherOut, "yaw", Yaw);
	Key(otherOut, "pitch", Pitch);
	Key(otherOut, "roll", Roll);
	Key(otherOut, "yawAxis", YawAxis);
	Key(otherOut, "pitchAxis", PitchAxis);
	Key(otherOut, "rollAxis", RollAxis);

	EndSection(otherOut);
}
