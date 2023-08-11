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

DEFAULT_BODY(UCameraComponent);

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
