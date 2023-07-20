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

#ifndef US_COMPONENT_HPP
#define	US_COMPONENT_HPP

#include "Core/Core.hpp"

class IComponent
{
public:
	IComponent() = default;
	virtual void Initialize() { /* override */ }
	virtual void Update(float deltaTime) { /* override */ }
	virtual void Destroy() { /* override */ }

	bool CanTick() const { return bComponentTick; }
protected:
	bool bComponentTick = false;
};

#endif // !US_COMPONENT_HPP