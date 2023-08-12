/*********************************************************************
 *   File: RenderClass.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_RENDER_CLASS_HPP
#define	US_RENDER_CLASS_HPP

#include "Core/MinimalCore.hpp"
#include <functional>

class URenderClass
{
	struct FFunctionRef
	{
		std::function<void(float)> Func;
	};
	using Functions = TMap<FString, FFunctionRef>;
public:
	virtual ~URenderClass()
	{
		refs.empty();
	}

	template<class ClassType, class Fx>
	void Register(ClassType* InClass, Fx&& function)
	{
		FFunctionRef ref{};
		ref.Func = std::bind(function, InClass, std::placeholders::_1);
		refs[InClass->GetId()] = ref;
	}
	template<class ClassType>
	void Remove(ClassType* OutClass)
	{
		refs.erase(OutClass->GetId());
	}
	void Draw(float deltaTime)
	{
		Functions::iterator it; for (it = refs.begin(); it != refs.end(); it++)
		{
			it->second.Func(deltaTime);
		}
	}
private:
	Functions refs;
};

#endif // !US_RENDER_CLASS_HPP