/*********************************************************************
 *   File: CameraComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Components/CameraComponent.hpp"
#include "Serializer/ComponentSerializer.hpp"

void UCameraComponent::Serialize(YAML::Emitter& otherOut)
{
	BeginComponentMap(otherOut);

	Key(otherOut, "near", Near);
	Key(otherOut, "far", Far);
	Key(otherOut, "fov", Fov);
	Key(otherOut, "yaw", Yaw);
	Key(otherOut, "pitch", Pitch);
	Key(otherOut, "roll", Roll);
	Key(otherOut, "yawaxis", YawAxis);
	Key(otherOut, "pitchaxis", PitchAxis);
	Key(otherOut, "rollaxis", RollAxis);

	EndMap(otherOut);
}

bool UCameraComponent::Deserialize(const FString& scenePath)
{
	return false;
}
