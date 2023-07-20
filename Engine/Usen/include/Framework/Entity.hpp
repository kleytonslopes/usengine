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
class UScene;

class UEntity : public UWeakClass
{
	using Super = UWeakClass;
public:
	UEntity(UScene* scene);

	void Initialize() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;
	virtual void OnConstruct();

	template<typename T>
	bool HasComponent()
	{
		/*if (components.Size() <= 0)
			return false;

		auto& comp = components.Get(typeid(T).name());
		if (!comp)
			return false;

		return true;*/

		if (components.size() <= 0)
			return false;

		auto& comp = components[typeid(T).name()];//components.Get(typeid(T).name());
		if (!comp)
			return false;

		return true;
	}

	template<typename T>
	IComponent& AddComponent()
	{
		T component{};
		components[typeid(T).name()] = &component;
		//components.Add(typeid(T).name(), &component);

		return component;
	}

protected:
	UScene* scene;
	TMap<FString, IComponent*> components;
	FString id;
	bool bTick = true;

	friend class UScene;
};

#endif // !US_ENTITY_HPP
