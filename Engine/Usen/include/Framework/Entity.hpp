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
#include "Components/MeshComponent.hpp"

class IComponent;
class UScene;

class UEntity : public UWeakClass
{
	DEFAULT_BODY(UWeakClass);
public:
	UEntity(UScene* scene);
	virtual ~UEntity();

	void Initialize() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;

	virtual void OnConstruct();

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
	IComponent* AddComponent()
	{
		T* component = new T(this);
		components[typeid(T).name()] = component;

		return static_cast<IComponent*>(component);
	}

	template<typename T, typename... Args>
	IComponent* AddComponent(Args&& ... args)
	{
		T* component = new T(std::forward<Args>(args)...);
		components[typeid(T).name()] = component;

		return static_cast<IComponent*>(component);
	}

	template<typename T>
	T* GetComponent()
	{
		return static_cast<T*>(components[typeid(T).name()]);
	}

protected:
	UScene* scene;
	TMap<FString, IComponent*> components;
	FString Id;
	bool bTick = true;

	bool bWasConstructed = false;

	friend class UScene;
};

#endif // !US_ENTITY_HPP
