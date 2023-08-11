/*********************************************************************
 *   File: ClassOf.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_CLASS_OF_HPP
#define	US_CLASS_OF_HPP

#include "Core/CommonTypes.hpp"
#include "Core/String.hpp"

template<typename Ty>
class TClassOf
{
public:
	TClassOf()	
	{
		Class = FConstructorHelper::CreateWeakObject<Ty>();
		IdentityClass = Class->GetIdentity();
	}
	~TClassOf()	{ }

	template<typename U>
	TClassOf& operator=(TClassOf<U>&& other)
	{
		if (Class)
		{
			FConstructorHelper::Destroy(Class);
			//delete Class;
			//Class = nullptr;
		}

		this->IdentityClass = other.IdentityClass;

		Class = other.Class->GetNew();//std::move(other.Class);
		return *this;
	}

	Ty* GetNew()
	{
		return new Ty(*Class->GetNew()); //FConstructorHelper::CreateObject<Ty>(*Class);
	}

	operator Ty* ()
	{
		return Class;
	}

	template<typename U>
	bool operator==(const TClassOf<U>&& other)
	{
		return other.Class->GetIdentity() == IdentityClass;
	}

	FString IdentityClass;
	Ty* Class = nullptr;
};

#endif // !US_CLASS_OF_HPP