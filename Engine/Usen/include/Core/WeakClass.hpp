/*********************************************************************
 *   File: WeakClass.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_WEAK_CLASS_HPP
#define	US_WEAK_CLASS_HPP

#include "Core/Core.hpp"
#include "WeakClass-generated.hpp"

class UWeakClass
{
	DEFAULT_BODY_GENERATED()
public:
	virtual void Initialize() { /* override */ }
	virtual void OnInitialized() { /* override */ }
	virtual void Update(float deltaTime) { /* override */ }
	virtual void OnDestroy();

	void Destroy();
protected:
	bool bWantDestroy = false;
	bool bIsDestroyed = false;
};

#endif // !US_WEAK_CLASS_HPP