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

#include "Components/Interface/IComponent.hpp"

class TransformComponent : public IComponent
{
public:
	TransformComponent() = default;

	uint32 X{ 0 };
	uint32 Y{ 0 };
	uint32 Z{ 0 };

	// Inherited via IComponent
	virtual void Initialize() override;
};
