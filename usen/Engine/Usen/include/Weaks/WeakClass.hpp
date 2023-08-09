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

	virtual void Create() = 0;
	virtual void PostCreate() = 0;

	virtual void Initialize() = 0;
	virtual void PostInitialize() = 0;

	virtual void Destroy() = 0;
	virtual void PostDestroy() = 0;

	FString GetId() const { return Id; }
	FString GetIdentity() const { return Identity; }

	virtual FString GetIdentity() { return "IWeakClass"; }

protected:
	FString Id;
	FString Identity;
	bool bIsInitialized = false;

	inline void SetIdentity(const FString& identity)
	{
		Identity = identity;
	}
};

#endif // !US_WEAK_CLASS_HPP