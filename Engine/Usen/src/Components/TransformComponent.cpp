/*********************************************************************
 *   File: TransformComponent.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Components/TransformComponent.hpp"

DEFAULT_BODY(UTransformComponent)

FVector UTransformComponent::GetLocation()
{
	return Transform.Location;
}

FVector UTransformComponent::GetOrigin()
{
	return Transform.Origin;
}

FVector UTransformComponent::GetRotation()
{
	return Transform.Rotation;
}

FVector UTransformComponent::GetScale()
{
	return Transform.Scale;
}

FVector UTransformComponent::GetUpVector()
{
	return Transform.UpVector;
}

FVector UTransformComponent::GetForwardVector()
{
	return Transform.ForwardVector;
}

FTransform UTransformComponent::GetTransform()
{
	return Transform;
}

FVector UTransformComponent::GetRightVector()
{
	return glm::normalize(glm::cross(Transform.UpVector, GetDirection()));
}

FVector UTransformComponent::GetDirection()
{
	return glm::normalize(Transform.Location - Transform.ForwardVector);
}

void UTransformComponent::SetTransform(const FTransform transform)
{
	SetLocation(transform.Location);
	SetOrigin(transform.Origin);
	SetRotation(transform.Rotation);
	SetScale(transform.Scale);
	SetUpVector(transform.UpVector);
	SetForwardVector(transform.ForwardVector);
}

void UTransformComponent::SetOrigin(const FVector& vector)
{
	Transform.Origin.x = vector.x;
	Transform.Origin.y = vector.y;
	Transform.Origin.z = vector.z;
}

void UTransformComponent::SetLocation(const FVector& vector)
{
	Transform.Location.x = vector.x;
	Transform.Location.y = vector.y;
	Transform.Location.z = vector.z;
}

void UTransformComponent::SetRotation(const FVector& vector)
{
	Transform.Rotation.x = vector.x;
	Transform.Rotation.y = vector.y;
	Transform.Rotation.z = vector.z;
}

void UTransformComponent::SetScale(const FVector& vector)
{
	Transform.Scale.x = vector.x;
	Transform.Scale.y = vector.y;
	Transform.Scale.z = vector.z;
}

void UTransformComponent::SetUpVector(const FVector& vector)
{
	Transform.UpVector.x = vector.x;
	Transform.UpVector.y = vector.y;
	Transform.UpVector.z = vector.z;
}

void UTransformComponent::SetForwardVector(const FVector& vector)
{
	Transform.ForwardVector.x = vector.x;
	Transform.ForwardVector.y = vector.y;
	Transform.ForwardVector.z = vector.z;
}

void UTransformComponent::Serialize(SeriFile& otherOut)
{
	BeginComponentSection(otherOut, Identity);

	Key(otherOut, "location", Transform.Location);
	Key(otherOut, "origin", Transform.Origin);
	Key(otherOut, "rotation", Transform.Rotation);
	Key(otherOut, "scale", Transform.Scale);
	Key(otherOut, "upVector", Transform.UpVector);
	Key(otherOut, "forwardVector", Transform.ForwardVector);

	EndSection(otherOut);
}

//bool UTransformComponent::Deserialize(const FString& scenePath)
//{
//	return false;
//}
