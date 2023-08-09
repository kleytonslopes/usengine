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

class ACamera : public AActor
{
	DEFAULT_BODY_GENERATED()
public:
	explicit ACamera();
	virtual ~ACamera();

	void Create() override;
	FMatrix4 GetView();
};

#endif // !US_CAMERA_HPP