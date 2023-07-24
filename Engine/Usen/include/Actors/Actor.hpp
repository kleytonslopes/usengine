/*********************************************************************
 *   File: Actor.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_ACTOR_HPP
#define	US_ACTOR_HPP


#include "Actors/Entity.hpp"
#include "Components/TransformComponent.hpp"
#include "Actor-generated.hpp"


class AActor : public AEntity
{
	DEFAULT_BODY_GENERATED()
public:
	explicit AActor();
	virtual ~AActor();
	void Destroy() override;

	void Create() override;

protected:
	TMap<FString, AComponent*> components;

	template<typename T>
	bool HasComponent()
	{
		if (components.size() <= 0)
			return false;

		auto& comp = components[typeid(T).name()];
		if (!comp)
			return false;

		return true;
	}

	template<typename T>
	T* AddComponent()
	{
		T* component = new T();
		components[typeid(T).name()] = component;

		return component;
	}

	template<typename T, typename... Args>
	T* AddComponent(Args&& ... args)
	{
		T* component = new T(std::forward<Args>(args)...);
		components[typeid(T).name()] = component;

		return component;
	}

	template<typename T>
	T* GetComponent()
	{
		return static_cast<T*>(components[typeid(T).name()]);
	}
};

#endif // !US_ACTOR_HPP