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
	return Transform.GetRightVector();//glm::normalize(glm::cross(Transform.GetUpVector(), GetDirection()));
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
	Transform.SetOrigin(vector);
}

void UTransformComponent::SetLocation(const FVector& vector)
{
	Transform.SetLocation(vector);
}

void UTransformComponent::SetRotation(const FVector& vector)
{
	Transform.SetRotation(vector);
}

void UTransformComponent::SetScale(const FVector& vector)
{
	Transform.SetScale(vector);
}

void UTransformComponent::SetUpVector(const FVector& vector)
{
	Transform.SetUpVector(vector);
}

void UTransformComponent::SetForwardVector(const FVector& vector)
{
	Transform.SetForwardVector(vector);
}

FVector UTransformComponent::GetWorldLocation()
{
	return Transform.GetWorldLocation();
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
