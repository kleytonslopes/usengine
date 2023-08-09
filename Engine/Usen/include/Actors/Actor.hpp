/*********************************************************************
 *   File: Actor.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_ACTOR_HPP
#define	US_ACTOR_HPP


#include "Actors/Entity.hpp"
#include "Components/TransformComponent.hpp"
#include "Actor-generated.hpp"

class UAttachment;

class AActor : public AEntity
{
	DEFAULT_BODY_GENERATED()
public:
	explicit AActor();
	virtual ~AActor();

	void Destroy() override;

	void Construct() override;

	void Create() override;
	void Initialize() override;
	void AttatchTo(AEntity* parent, FAttachmentSettings& attachmentSettings) override;
	void DetachFromParent() override;
	void Detach(AActor* entity);

	void SetTransform(const FTransform& transform);
	void Update(float deltaTime) override;

	FVector GetLocation();
	FVector GetSceneLocation();
	FTransform& GetTransform();

	void SetLocation(const FVector& location);
	

protected:
	UAttachment* Attachments = nullptr;
	TMap<FString, AComponent*> components;

	void Serialize(SeriFile& otherOut) override;

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
		component->Construct();
		component->Create();

		return component;
	}

	template<typename T, typename... Args>
	T* AddComponent(Args&& ... args)
	{
		T* component = new T(std::forward<Args>(args)...);
		components[typeid(T).name()] = component;
		component->Construct();
		component->Create();

		return component;
	}

	template<typename T>
	T* GetComponent()
	{
		return static_cast<T*>(components[typeid(T).name()]);
	}

	void Draw(float deltaTime) override;

	friend class FEntitySerializer;
	friend class UScene;
};

#endif // !US_ACTOR_HPP