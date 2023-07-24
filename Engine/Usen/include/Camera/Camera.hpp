/*********************************************************************
 *   File: Camera.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CAMERA_HPP
#define	US_CAMERA_HPP


#include "Actors/Entity.hpp"
#include "Camera-generated.hpp"

class ACamera : public AEntity
{
	DEFAULT_BODY_GENERATED()
public:
	explicit ACamera();
	virtual ~ACamera();

	void Create() override;
};

#endif // !US_CAMERA_HPP