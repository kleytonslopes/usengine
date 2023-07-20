/*********************************************************************
 *   File: Camera.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CAMERA_HPP
#define	US_CAMERA_HPP

#include "Framework/Entity.hpp"

class UCamera : public UEntity
{
	using Super = UEntity;

public:
	using UEntity::UEntity;

	// Inherited via UEntity
	virtual void OnConstruct() override;

};

#endif // !US_CAMERA_HPP