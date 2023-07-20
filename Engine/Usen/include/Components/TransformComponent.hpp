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
public:
	UTransformComponent() = default;

	uint32 X{ 0 };
	uint32 Y{ 0 };
	uint32 Z{ 0 };

	// Inherited via IComponent
	virtual void Initialize() override;
};

#endif // !US_TRANSFORM_COMPONENT_HPP