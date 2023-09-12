/*********************************************************************
 *   File: Component.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: July 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Components/Component.hpp"
#include "Actors/Actor.hpp"

DEFAULT_BODY(AComponent)

void AComponent::SetParent(AActor* parent)
{
	this->Parent = parent;
}

FVector AComponent::GetParentLocation()
{
	if (Parent)
	{
		//AActor* aParent = Cast<AActor*>(Parent);
		//if (aParent)
		//{
		//	return aParent->GetLocation();
		//}

		return Parent->GetLocation();
	}
	return FVector{0};
}

AFTransform AComponent::GetParentTransform()
{
	if (Parent)
	{
		//AActor* aParent = Cast<AActor*>(Parent);
		//if (aParent)
		//{
		//	return aParent->GetTransform();
		//}

		return Parent->GetTransform();
	}
	return TrasnformComponent;
}

FVector AComponent::GetLocation()
{
	if (Parent)
	{
		//AActor* aParent = Cast<AActor*>(Parent);
		//if (aParent)
		//{
		//	return aParent->GetLocation();
		//}

		return Parent->GetLocation();
	}
	return TrasnformComponent.GetLocation();
}

FVector AComponent::GetUpVector()
{
	if (Parent)
	{
		//AActor* aParent = Cast<AActor*>(Parent);
		//if (aParent)
		//{
		//	return aParent->GetUpVector();
		//}

		return Parent->GetUpVector();
	}
	return TrasnformComponent.GetUpVector();
}

FVector AComponent::GetForwardVector()
{
	if (Parent)
	{
		//AActor* aParent = Cast<AActor*>(Parent);
		//if (aParent)
		//{
		//	return aParent->GetForwardVector();
		//}

		return Parent->GetForwardVector();
	}
	return TrasnformComponent.GetForwardVector();
}

FVector AComponent::GetRightVector()
{
	if (Parent)
	{
		//AActor* aParent = Cast<AActor*>(Parent);
		//if (aParent)
		//{
		//	return aParent->GetRightVector();
		//}

		return Parent->GetRightVector();
	}
	return TrasnformComponent.GetRightVector();
}

void AComponent::BeginComponentSection(SeriFile& otherOut, const FString& identity)
{
	Key(otherOut, identity);
	BeginSection(otherOut);
	Key(otherOut, "id", GetId());
}
