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

class UEntity;

class IComponent
{
public:
	IComponent(UEntity* Owner);
	virtual ~IComponent();

	virtual void Initialize();
	virtual void Update(float deltaTime) { /* override */ }
	virtual void Destroy() { /* override */ }

	bool CanTick() const { return bComponentTick; }
protected:
	FString Id;
	bool bComponentTick = false;

	UEntity* Owner;
};

#endif // !US_COMPONENT_HPP