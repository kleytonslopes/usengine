/*********************************************************************
 *   File: Entity.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_ENTITY_HPP
#define	US_ENTITY_HPP

#include "Core/WeakClass.hpp"
#include "Components/TransformComponent.hpp"

class IComponent;
#define QUOTE(x) #x
class Entity : public UWeakClass
{
	using Super = UWeakClass;
public:
	Entity() = default;

	void Initialize() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;

	template<typename T>
	bool HasComponent()
	{
		if (components.Size() <= 0)
			return false;

		auto& comp = components.Get(typeid(T).name());
		if (!comp)
			return false;

		return true;
	}

	template<typename T>
	IComponent& AddComponent()
	{
		T component{};
		components.Add(typeid(T).name(), &component);

		return component;
	}

protected:
	Map<FString, IComponent*> components;
};

#endif // !US_ENTITY_HPP
