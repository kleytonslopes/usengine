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
	return Transform.GetLocation();
}

FVector UTransformComponent::GetOrigin()
{
	return Transform.GetOrigin();
}

FVector UTransformComponent::GetRotation()
{
	return Transform.GetRotation();
}

FVector UTransformComponent::GetScale()
{
	return Transform.GetScale();
}

FVector UTransformComponent::GetUpVector()
{
	return Transform.GetUpVector();
}

FVector UTransformComponent::GetForwardVector()
{
	return Transform.GetForwardVector();
}

FTransform UTransformComponent::GetTransform()
{
	return Transform;
}

FVector UTransformComponent::GetRightVector()
{
	return glm::normalize(glm::cross(Transform.GetUpVector(), GetDirection()));
}

FVector UTransformComponent::GetDirection()
{
	return glm::normalize(Transform.GetLocation() - Transform.GetForwardVector());
}

void UTransformComponent::SetTransform(FTransform transform)
{
	SetLocation(transform.GetLocation());
	SetOrigin(transform.GetOrigin());
	SetRotation(transform.GetRotation());
	SetScale(transform.GetScale());
	SetUpVector(transform.GetUpVector());
	SetForwardVector(transform.GetForwardVector());
}

void UTransformComponent::SetOrigin(const FVector& vector)
{
	Transform.GetOrigin().x = vector.x;
	Transform.GetOrigin().y = vector.y;
	Transform.GetOrigin().z = vector.z;
}

void UTransformComponent::SetLocation(FVector& vector)
{
	Transform.GetLocation().x = vector.x;
	Transform.GetLocation().y = vector.y;
	Transform.GetLocation().z = vector.z;
}

void UTransformComponent::SetRotation(const FVector& vector)
{
	Transform.GetRotation().x = vector.x;
	Transform.GetRotation().y = vector.y;
	Transform.GetRotation().z = vector.z;
}

void UTransformComponent::SetScale(const FVector& vector)
{
	Transform.GetScale().x = vector.x;
	Transform.GetScale().y = vector.y;
	Transform.GetScale().z = vector.z;
}

void UTransformComponent::SetUpVector(const FVector& vector)
{
	Transform.GetUpVector().x = vector.x;
	Transform.GetUpVector().y = vector.y;
	Transform.GetUpVector().z = vector.z;
}

void UTransformComponent::SetForwardVector(const FVector& vector)
{
	Transform.GetForwardVector().x = vector.x;
	Transform.GetForwardVector().y = vector.y;
	Transform.GetForwardVector().z = vector.z;
}

void UTransformComponent::Serialize(SeriFile& otherOut)
{
	BeginComponentSection(otherOut, Identity);

	Key(otherOut, "location", Transform.GetLocation());
	Key(otherOut, "origin", Transform.GetOrigin());
	Key(otherOut, "rotation", Transform.GetRotation());
	Key(otherOut, "scale", Transform.GetScale());
	Key(otherOut, "upVector", Transform.GetUpVector());
	Key(otherOut, "forwardVector", Transform.GetForwardVector());

	EndSection(otherOut);
}

//bool UTransformComponent::Deserialize(const FString& scenePath)
//{
//	return false;
//}
