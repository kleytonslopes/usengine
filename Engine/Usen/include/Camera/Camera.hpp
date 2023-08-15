/*********************************************************************
 *   File: Camera.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CAMERA_HPP
#define	US_CAMERA_HPP


#include "Actors/Actor.hpp"
#include "Camera-generated.hpp"

class UCameraComponent;

class ACamera : public AActor
{
	DEFAULT_BODY_GENERATED()
public:
	void Construct() override;
	FMatrix4 GetView();

	void SetRotation(FVector& vector) override;
	
	float GetFieldOfView() const;
	float GetNear() const;
	float GetFar() const;
private:
	UCameraComponent* CameraComponent = nullptr;
};

#endif // !US_CAMERA_HPP