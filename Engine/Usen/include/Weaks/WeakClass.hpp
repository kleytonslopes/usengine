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

#include "Core/MinimalCore.hpp"
#include "WeakClass-generated.hpp"

class IWeakClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit IWeakClass();
	virtual ~IWeakClass();

	virtual void Initialize() = 0;
	virtual void Destroy() = 0;
protected:
	bool bIsInitialized = false;
};

#endif // !US_WEAK_CLASS_HPP