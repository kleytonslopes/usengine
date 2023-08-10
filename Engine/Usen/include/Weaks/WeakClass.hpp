/*********************************************************************
 *   File: WeakClass.hpp
 *  Brief: Sequence to initialize a instance
 * 
 * 1º Call Constructor  - this call PostConstruct
 *    -   Constructor(): This method should be used for setup defaults properties
 *    - PostConstruct(): This method should be used for initialize instances and pointers
 * 
 * 2º Call Create       - this call PostCreate
 * 3º Call Initialize   - this call PostInitialize
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

	virtual void Construct();
	virtual void PostConstruct();

	virtual void Initialize();
	virtual void PostInitialize();

	virtual void Destroy();
	virtual void PostDestroy();

	virtual void Tick(float deltaTime);

	FString GetId() const { return Id; }
	FString GetIdentity() const { return Identity; }

	virtual FString GetIdentity() { return "IWeakClass"; }

protected:
	FString Id;
	FString Identity;

	bool bIsConstructed = false;
	bool bIsCreated = false;
	bool bIsInitialized = false;
	bool bIsDestroyed = false;

	bool bTick = false;

	inline void SetIdentity(const FString& identity)
	{
		Identity = identity;
	}

	friend class FConstructorHelper;
};

#endif // !US_WEAK_CLASS_HPP