/*********************************************************************
 *   File: ConstructorHelper.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CONSTRUCTOR_HELPER_HPP
#define	US_CONSTRUCTOR_HELPER_HPP

#include "Core/MinimalCore.hpp"

class FConstructorHelper
{
	
public:
	explicit FConstructorHelper();
	virtual ~FConstructorHelper();

	template<class T, class U>
	static void MakeClassOf(TClassOf<U>& targetClassOf);

	template<class T, class U>
	static T* CreateObject(TClassOf<U>& targetClassOf);

	template<class T>
	static T* CreateObject();
};

#endif // !US_CONSTRUCTOR_HELPER_HPP

template<class T, class U>
inline void FConstructorHelper::MakeClassOf(TClassOf<U>& targetClassOf)
{
	targetClassOf = TClassOf<T>();
}

template<class T, class U>
inline T* FConstructorHelper::CreateObject(TClassOf<U>& targetClassOf)
{
	return new T(*targetClassOf.Class.get());
}

template<class T>
inline T* FConstructorHelper::CreateObject()
{
	T* object = new T();
	object->Construct();
	object->PostConstruct();

	return object;
}
