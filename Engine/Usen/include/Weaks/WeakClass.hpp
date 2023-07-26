/*********************************************************************
 *   File: WeakClass.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_WEAK_CLASS_HPP
#define	US_WEAK_CLASS_HPP

#include "Core/MinimalCore.hpp"


class IWeakClass
{

public:
	explicit IWeakClass();
	virtual ~IWeakClass();

	virtual void Initialize() = 0;
	virtual void Destroy() = 0;
protected:
	bool bIsInitialized = false;
	FString Identity;

	inline void SetIdentity(FString identity)
	{
		Identity = identity;
	}
};

#endif // !US_WEAK_CLASS_HPP