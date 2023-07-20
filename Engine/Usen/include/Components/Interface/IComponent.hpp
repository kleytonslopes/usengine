/*********************************************************************
 *   File: IComponent.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#include "Core/Core.hpp"

class IComponent
{
public:
	IComponent() = default;
	virtual void Initialize() = 0;
};
