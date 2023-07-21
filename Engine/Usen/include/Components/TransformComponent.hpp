/*********************************************************************
 *   File: TransformComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_TRANSFORM_COMPONENT_HPP
#define	US_TRANSFORM_COMPONENT_HPP

#include "Components/Interface/IComponent.hpp"

class UTransformComponent : public IComponent
{
	DEFAULT_BODY(IComponent);

public:
	UTransformComponent(UEntity* Parent);

	FVector GetLocation();
	FVector GetRotation();
	FVector GetScale();
	FVector GetUpVector();
	FVector GetForwardVector();

	FVector GetRightVector();
	FVector GetDirection();

	void SetLocation(const FVector& vector);
	void SetRotation(const FVector& vector);
	void SetScale(const FVector& vector);
	void SetUpVector(const FVector& vector);
	void SetForwardVector(const FVector& vector);

private:
	FVector Location{ 0.f, 0.f, 0.f };
	FVector Rotation{ 0.f, 0.f, 0.f };
	FVector Scale{ 1.f, 1.f, 1.f };
	FVector UpVector{ 0.f, 1.f, 0.f };
	FVector ForwardVector{ 0.f, 0.f, -1.f };
};

#endif // !US_TRANSFORM_COMPONENT_HPP