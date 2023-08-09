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

//#include "Core/MinimalCore.hpp"
#include "Core/CommonTypes.hpp"
#include "Core/String.hpp"

template<typename Ty>
class TClassOf
{
public:
	TClassOf()	
	{
		Class = std::make_shared<Ty>();
	}
	~TClassOf()	{ }

	template<typename U>
	TClassOf& operator=(const TClassOf<U>&& other)
	{
		//if (*this == *other)
		//	return *this;

		if (Class)
			Class.reset();

		IdentityClass = other.Class.get()->GetIdentity();
		Class = std::move(other.Class);
		return *this;
	}

	Ty* GetNew()
	{
		return new Ty(*Class.get());
	}

	operator Ty* ()
	{
		return Class.get();
	}

	template<typename U>
	bool operator==(const TClassOf<U>&& other)
	{
		return other.Class.get()->GetIdentity() == IdentityClass;
	}

	FString IdentityClass;
	std::shared_ptr<Ty> Class;
};

#endif // !US_CLASS_OF_HPP