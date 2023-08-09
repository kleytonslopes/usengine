/*********************************************************************
 *   File: TickClass.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef UK_TICK_CLASS_HPP
#define	UK_TICK_CLASS_HPP

#include "Core/MinimalCore.hpp"
#include <functional>

class UTickClass
{
	struct FFunctionRef 
	{
		void* Ref = nullptr; 
		std::function<void(float)> Func;
	}; 
using Functions = TMap<FString, FFunctionRef>; 
public: 
	virtual ~UTickClass() { } 

	template<class ClassType, class Fx> 
	void Register(ClassType* InClass, Fx&& function)
	{
		FFunctionRef ref{};
		ref.Func = std::bind(function, InClass, std::placeholders::_1); 
		ref.Ref = InClass; refs[InClass->GetId()] = ref;
	} 
	template<class ClassType>
	void Remove(ClassType* OutClass)
	{
		refs.erase(OutClass->GetId());
	} 
	void Tick(float deltaTime)
	{
		Functions::iterator it; for (it = refs.begin(); it != refs.end(); it++) 
		{
			it->second.Func(deltaTime);
		}
	} 
private: 
	Functions refs;
};


#endif // !UK_TICK_CLASS_HPP