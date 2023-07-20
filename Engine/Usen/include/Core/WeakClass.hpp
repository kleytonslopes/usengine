/*********************************************************************
 *   File: WeakClass.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_WEAK_CLASS_HPP
#define	US_WEAK_CLASS_HPP

#include "Core/Core.hpp"

class UWeakClass
{
public:
	virtual void Initialize() { /* override */ }
	virtual void OnInitialized() { /* override */ }
	virtual void Update(float deltaTime) { /* override */ }
};

#endif // !US_WEAK_CLASS_HPP