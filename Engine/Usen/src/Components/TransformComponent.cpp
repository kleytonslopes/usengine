/*********************************************************************
 *   File: TransformComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Components/TransformComponent.hpp"
#include "Framework/Entity.hpp"

UTransformComponent::UTransformComponent(UEntity* Parent)
	: Super(Parent)
{
	bComponentTick = false;
}

FVector UTransformComponent::GetLocation()
{
	return Location;
}

FVector UTransformComponent::GetRotation()
{
	return Rotation;
}

FVector UTransformComponent::GetScale()
{
	return Scale;
}

FVector UTransformComponent::GetUpVector()
{
	return UpVector;
}

FVector UTransformComponent::GetForwardVector()
{
	return ForwardVector;
}

FVector UTransformComponent::GetRightVector()
{
	return glm::normalize(glm::cross(UpVector, GetDirection()));
}

FVector UTransformComponent::GetDirection()
{
	return glm::normalize(Location - ForwardVector);
}

void UTransformComponent::SetLocation(const FVector& vector)
{
	Location.x = vector.x;
	Location.y = vector.y;
	Location.z = vector.z;
}

void UTransformComponent::SetRotation(const FVector& vector)
{
	Rotation.x = vector.x;
	Rotation.y = vector.y;
	Rotation.z = vector.z;
}

void UTransformComponent::SetScale(const FVector& vector)
{
	Scale.x = vector.x;
	Scale.y = vector.y;
	Scale.z = vector.z;
}

void UTransformComponent::SetUpVector(const FVector& vector)
{
	UpVector.x = vector.x;
	UpVector.y = vector.y;
	UpVector.z = vector.z;
}

void UTransformComponent::SetForwardVector(const FVector& vector)
{
	ForwardVector.x = vector.x;
	ForwardVector.y = vector.y;
	ForwardVector.z = vector.z;
}
