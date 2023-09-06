/*********************************************************************
 *   File: TransformComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_TRANSFORM_COMPONENT_HPP
#define	US_TRANSFORM_COMPONENT_HPP


#include "Components/Component.hpp"
#include "TransformComponent-generated.hpp"

//struct FTransform
//{
//	FVector Location{ 0.f, 0.f, 0.f };
//	FVector Origin{ 0.f, 0.f, 0.f };
//	FVector Rotation{ 0.f, 0.f, 0.f };
//	FVector Scale{ 1.f, 1.f, 1.f };
//	FVector UpVector{ 0.f, 1.f, 0.f };
//	FVector ForwardVector{ 0.f, 0.f, -1.f };
//};

class UTransformComponent : public AComponent
{
	DEFAULT_BODY_GENERATED()
public:
	FVector GetLocation();
	FVector GetOrigin();
	FVector GetRotation();
	FVector GetScale();
	FVector GetUpVector();
	FVector GetForwardVector();
	AFTransform GetTransform();

	FVector GetRightVector();
	FVector GetDirection();

	void SetTransform(AFTransform transform);
	void SetOrigin(const FVector& transform);
	void SetLocation(FVector& vector);
	void SetRotation(const FVector& vector);
	void SetScale(const FVector& vector);
	void SetUpVector(const FVector& vector);
	void SetForwardVector(const FVector& vector);

	FVector GetWorldLocation();

protected:
	void Serialize(SeriFile& otherOut) override;

private:
	AFTransform Transform{};
};

#endif // !US_TRANSFORM_COMPONENT_HPP