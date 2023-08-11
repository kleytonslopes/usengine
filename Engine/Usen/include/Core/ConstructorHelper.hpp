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
#include "Weaks/WeakClass.hpp"
class FConstructorHelper
{

public:
	explicit FConstructorHelper();
	virtual ~FConstructorHelper();

	template<class T, class U>
	inline static void MakeClassOf(TClassOf<U>& targetClassOf)
	{
		targetClassOf = TClassOf<T>();
	}

	template<class T>
	inline static T* CreateWeakObject()
	{
		T* object = new T();
		return object;
	}

	template<class T, class U>
	inline static TClassOf<T> GetClassOf(TClassOf<U>& targetClassOf)
	{
		targetClassOf = TClassOf<U>();

		return TClassOf<U>();
	}

	template<class T, class U>
	inline static T* CreateObject(const TClassOf<U>& targetClassOf)
	{
		//T* test = *targetClassOf.Class;
		T* object = targetClassOf.Class->GetNew();//new T(*targetClassOf.Class);
		object->Construct();
		object->PostConstruct();

		return object;
	}

	template<class T>
	inline static T* CreateObject()
	{
		T* object = new T();
		object->Construct();
		object->PostConstruct();

		return object;
	}

	template<class T>
	inline static void Destroy(T* objectToDestroy)
	{
		try
		{
			if (objectToDestroy)
			{
				objectToDestroy->Destroy();
				objectToDestroy->PostDestroy();
			}

			delete objectToDestroy;
			
		}
		catch (const std::exception& ex)
		{
			ULOG_Error(FText::Format("Failed on Delete: %s", ex.what()));
		}
		objectToDestroy = nullptr;
	}
};

#endif // !US_CONSTRUCTOR_HELPER_HPP
